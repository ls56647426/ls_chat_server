/*
 * =====================================================================================
 *
 *       Filename:  server.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/19/2020 01:36:54 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef _SERVER_H_
#define _SERVER_H_

#include <event2/listener.h>
#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <event2/event.h>
#include <event.h>

#include <string>
#include <map>
#include <algorithm>
#include <list>
using namespace std;

#include "include/Msg.h"

typedef struct
{
	string code; 					/* 验证码 */
	string email; 					/* 邮箱 / 手机号 */
	struct timeval indate; 			/* 到期时间 */
	struct bufferevent *bev; 		/* 当前连接的bev */
} Verify;

/* 用户在线列表 */
static map<uint32_t, struct bufferevent *> onlineMap;

/* 验证信息列表 */
static list<Verify> verifyList;

static void read_cb(struct bufferevent *bev, void *arg);
static void write_cb(struct bufferevent *bev, void *arg);
static void event_cb(struct bufferevent *bev,short events, void *arg);
static void listener_cb(struct evconnlistener* listener, evutil_socket_t fd,
				struct sockaddr *addr, int len, void *ptr);
static void signal_cb(evutil_socket_t, short, void *);
//static void udp_cb(const int sock, short int which, void *arg);

string packet(const string &msgStr);
string unpacket(evbuffer *input);
string unpacket(char *input, uint32_t size);
Msg jsonToMsg(const string &jsonStr);
void getFriend(struct bufferevent *bev, Msg &msg);

#endif

