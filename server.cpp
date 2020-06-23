/*
 * =====================================================================================
 *
 *       Filename:  server.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/19/2020 11:27:31 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

/* c std lib */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

/* unix lib */
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <pthread.h>
#include <signal.h>

/* c++ lib */
#include <iostream>

/* third-party lib */
#include <event2/listener.h>
#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <event2/event.h>

/* custom lib */
#include "server.h"
#include "include/Msg.h"

#define SERV_PORT 5664
#define SERV_IP "112.124.19.14"

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
int main ( int argc, char *argv[] )
{
	/* 初始化服务器地址结构 */
	struct sockaddr_in serv_addr;
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
//	inet_pton(AF_INET, SERV_IP, &serv_addr.sin_addr.s_addr);
	serv_addr.sin_port = htons(SERV_PORT);

	//创建event_base
	struct event_base *base;
	base = event_base_new();

	//创建监听器
	struct evconnlistener *listener;
	listener = evconnlistener_new_bind(base, listener_cb, base, 
			LEV_OPT_CLOSE_ON_FREE | LEV_OPT_REUSEABLE, -1, 
			(struct sockaddr*)&serv_addr, sizeof(serv_addr));

	/* 注册普通的信号事件 */
	struct event *signal_event = evsignal_new(base, SIGINT, signal_cb, base);
	if(!signal_event || event_add(signal_event, NULL) < 0)
	{
		fprintf(stderr, "信号事件注册失败!\n");
		exit(1);
	}

	//启动循环监听
	event_base_dispatch(base);

	//释放操作
	evconnlistener_free(listener);
	event_base_free(base);

	return EXIT_SUCCESS;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  read_cb
 *  Description:  
 * =====================================================================================
 */
void read_cb(struct bufferevent *bev, void *arg)
{
	char buf[BUFSIZ];

	bufferevent_read(bev, buf, BUFSIZ);

	cout << "clinet:" << buf << endl;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  write_cb
 *  Description:  
 * =====================================================================================
 */
void write_cb(struct bufferevent *bev, void *arg)
{
	printf("成功写数据给客户端,写缓冲区回调函数被回调.\n");
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  event_cb
 *  Description:  
 * =====================================================================================
 */
void event_cb(struct bufferevent *bev,short events, void *arg)
{
	if (events & BEV_EVENT_EOF)
	{
		printf("连接关闭。\n");
	} 
	else if(events & BEV_EVENT_ERROR)
	{
		printf("连接出现错误！\n");
	}

	bufferevent_free(bev);

	printf("bufferevent 资源已经被释放.\n");
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  listener_cb
 *  Description:  
 * =====================================================================================
 */
void listener_cb(struct evconnlistener* listener, evutil_socket_t fd,
		struct sockaddr *addr, int len, void *ptr)
{
	struct event_base *base = (struct event_base*)ptr;
	char buf[256];

	struct sockaddr_in *clie_addr = (struct sockaddr_in *)addr;
	evutil_inet_ntop(clie_addr->sin_family, &clie_addr->sin_addr, buf, sizeof(buf));
	printf("新的连接%d, IP: %s\n", fd, buf);

	//添加新事件
	struct bufferevent* bev;
	bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);

	//给bufferevent缓冲区设置回调
	bufferevent_setcb(bev, read_cb, write_cb, event_cb, NULL);

	//启动bufferevent的读缓冲区，默认是disable的.
	bufferevent_enable(bev, EV_READ);
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  signal_cb
 *  Description:  
 * =====================================================================================
 */
void signal_cb(evutil_socket_t sig, short events, void *arg)
{
	struct event_base *base = (struct event_base *)arg;
	struct timeval delay = {2, 0};

	/* 退出处理 */

	printf("\n接受到关闭信号，程序将在2秒后退出。。。\n");

	event_base_loopexit(base, &delay);
}

