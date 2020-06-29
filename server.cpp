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
#include <zlib.h>
#include <json/json.h>

/* custom lib */
#include "server.h"
#include "include/Msg.h"
#include "service/UserService.h"

#define SERV_PORT 5664
#define SERV_IP "112.124.19.14"

UserService us;

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  服务器端主函数
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
 *  Description:  读缓冲区回调函数
 * =====================================================================================
 */
void read_cb(struct bufferevent *bev, void *arg)
{
	printf("read_cb收到数据。\n");
	Msg msg;
	Group grp;
	User src, dest, *u_tmp;
	MsgInfo info;
	string msgStr;
	string destStr;
	struct evbuffer *input = bufferevent_get_input(bev);
	struct evbuffer *output = bufferevent_get_output(bev);
	int tmp;

	/* 解析数据包 */
	msgStr = unpacket(input);
	if(msgStr == "")
	{
		printf("解析数据包出错。\n");
		return;
	}

	/* 提取json数据 */
	Json::CharReaderBuilder b;
    Json::CharReader* reader(b.newCharReader());
    Json::Value root;
    JSONCPP_STRING errs;
    bool ok = reader->parse(msgStr.data(), msgStr.data() + msgStr.size(), &root, &errs);
    if (!ok || errs.size() != 0)
    {
        printf("invalid json: %s\n", msgStr.data());
        delete reader;
        return;
    }
    delete reader;

	msg.setType(root["type"].asInt());
	
	grp.setId(root["group"]["id"].asInt());
	grp.setName(root["group"]["name"].asString());
	msg.setGroup(grp);
	
	src.setId(root["src"]["id"].asInt());
	src.setUsername(root["src"]["username"].asString());
	src.setPassword(root["src"]["password"].asString());
	src.setMobile(root["src"]["mobile"].asString());
	src.setStatus(root["src"]["status"].asInt64());
	msg.setSrc(src);

	dest.setId(root["dest"]["id"].asInt());
	dest.setUsername(root["dest"]["username"].asString());
	dest.setPassword(root["dest"]["password"].asString());
	dest.setMobile(root["dest"]["mobile"].asString());
	dest.setStatus(root["dest"]["status"].asInt());
	msg.setDest(dest);

	info.setInfo(root["info"]["info"].asString());
	msg.setInfo(info);

	/* 解析并处理 */
	switch(msg.getType())
	{
		case MsgType::MSG_HEARTBEAT: 		/* 心跳包 */
			/* 封包 + 发送 */
			destStr = packet(msg.toString());
			evbuffer_add(output, destStr.data(), destStr.size());
			break;
		case MsgType::MSG_LOGIN: 			/* 登录 */
			/* 登录校验 */
			u_tmp = us.findUserByUsernameAndPassword(
					msg.getSrc().getUsername(),
					msg.getSrc().getPassword()
					);

			/* 查无此人 */
			if(!u_tmp)
			{
				msg.setType(MsgType::ERRNO_INEXISTENCE);
				destStr = packet(msg.toString());
				evbuffer_add(output, destStr.data(), destStr.size());
				return;
			}
			
			/* 登录成功 */
			/* 登录 */
			tmp = u_tmp->getId();
			if(onlineMap[tmp] == 0)
				onlineMap[tmp] = bev;
			/* 挤掉 */
			else
			{
				/* 通知被挤掉的人 */
				msg.setType(ERRNO_BEOFFLINE);
				destStr = packet(msg.toString());
				bufferevent_write(onlineMap[tmp], destStr.data(), destStr.size());
				onlineMap[tmp] = bev;
				return;
			}
			/* 修改在线状态 */
			u_tmp->setStatus(UserStatus::USER_STAT_ONLINE);
			us.updateUser(*u_tmp);
			/* 返回用户其他(全部)数据 */
			msg.setType(MsgType::ERRNO_SUCCESS);
			msg.setSrc(*u_tmp);
			destStr = packet(msg.toString());
			evbuffer_add(output, destStr.data(), destStr.size());
			break;
		case MsgType::MSG_REGISTER: 		/* 注册 */
			/* 调用service层，直接返回结果 */
			msg.setType(us.addUser(msg.getSrc()));
			destStr = packet(msg.toString());
			evbuffer_add(output, destStr.data(), destStr.size());
			break;
		default: break;
	}
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  write_cb
 *  Description:  写缓冲区回调函数
 * =====================================================================================
 */
void write_cb(struct bufferevent *bev, void *arg)
{
	printf("成功写数据给客户端,写缓冲区回调函数被回调.\n");
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  event_cb
 *  Description:  服务器端事件处理回调函数
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
	else if(events & BEV_EVENT_CONNECTED)
	{
		printf("event_cb,新的连接成功。");
		return;
	}

	bufferevent_free(bev);

	/* 下线处理 */
	auto find_item = find_if(onlineMap.begin(), onlineMap.end(),
			[bev](const map<uint32_t, struct bufferevent *>::value_type item)
			{
			return item.second == bev;
			});
	if (find_item != onlineMap.end())
	{
		/* 数据库状态更新 */
		User *user = us.findUserById(find_item->first);
		user->setStatus(UserStatus::USER_STAT_OFFLINE);
		us.updateUser(*user);

		/* 删除在线列表 */
		onlineMap.erase(find_item);
	}

	printf("bufferevent 资源已经被释放.\n");
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  listener_cb
 *  Description:  服务器端监听事件回调函数
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
 *  Description:  Ctrl+C信号回调函数
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

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  packet
 *  Description:  封装数据包
 * 					将json数据 压缩/不压缩(默认压缩) 后，插入包头，返回结果
 * =====================================================================================
 */
string packet(const string &msgStr)
{
	char *res;
	char buf[BUFSIZ];
	uint32_t resLen;
	MsgHeader header;
	header.compressflag = MsgHeaderType::COMPRESSED;
	header.originsize = msgStr.size();
	header.compresssize = compressBound(header.originsize);

	/* 压缩，插入消息头 */
	if(header.compressflag == MsgHeaderType::COMPRESSED)
	{
		/* 压缩数据 */
		compress((Bytef*)buf, (uLongf*)&header.compresssize, (Bytef*)msgStr.data(), header.originsize);

		/* 压缩校验 */
		if(header.compresssize <= 0 ||
				header.compresssize > MSGINFO_MAX_LEN)
		{
			printf("压缩结果错误。\n");
			return "";
		}

		resLen = sizeof(header) + header.compresssize;
		res = new char[resLen];
		memcpy(res, &header, sizeof(header));
		memcpy(res + sizeof(header), buf, header.compresssize);
	}
	else
	{
		resLen = sizeof(header) + header.originsize;
		res = new char[resLen];
		memcpy(res, &header, sizeof(header));
		memcpy(res + sizeof(header), msgStr.data(), header.originsize);
	}

	return string(res, resLen);
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  unpacket
 *  Description:  解析数据包
 *  				解析从客户端发来的数据包
 *  				解压并去掉包头，剩Msg的json数据
 * =====================================================================================
 */
string unpacket(evbuffer *input)
{
	char *res;
	MsgHeader header;
	uint32_t len = evbuffer_get_length(input);

	/* 解析数据包 */
	if(len < sizeof(header))
	{
		printf("收到数据，但长度不足，等待下次传输：%d\n", len);
		return "";
	}

	/* 获取数据头 */
	evbuffer_copyout(input, &header, sizeof(header));

	/* 压缩过，需要解压数据包再提取 */
	if(header.compressflag == MsgHeaderType::COMPRESSED)
	{
		/* 包头有错误，立即关闭连接 */
		if(header.originsize <= 0 ||
				header.originsize > MSGINFO_MAX_LEN ||
				header.compresssize <= 0 ||
				header.compresssize > MSGINFO_MAX_LEN)
		{
			printf("包头错误：%d, %d\n", header.originsize, header.compresssize);
			return "";
		}

		/* 收到的数据不够一个完整的数据包 */
		if(len < sizeof(header) + header.compresssize)
			return "";

		/* 获取数据 */
		char *buf = new char[header.compresssize];
		evbuffer_remove(input, &header, sizeof(header));
		evbuffer_remove(input, buf, header.compresssize);

		/* 解压数据 */
		res = new char[header.originsize];
		int ret;
		if((ret = uncompress((Bytef*)res, (uLongf*)&header.originsize, (Bytef*)buf, header.compresssize)) != Z_OK)
		{
			printf("解压失败 %d：%d\n", ret, header.originsize);
			return "";
		}
	}
	/* 没压缩过，直接提取 */
	else
	{
		/* 包头有错误，立即关闭连接 */
		if(header.originsize <= 0 ||
				header.originsize > MSGINFO_MAX_LEN)
		{
			printf("包头错误：%d\n", header.originsize);
			return "";
		}

		/* 收到的数据不够一个完整的数据包 */
		if((uint32_t)len < sizeof(header) + header.originsize)
			return "";

		/* 获取数据 */
		res = new char[header.originsize];
		evbuffer_remove(input, &header, sizeof(header));
		evbuffer_remove(input, res, header.originsize);
	}

	return string(res, header.originsize);
}

