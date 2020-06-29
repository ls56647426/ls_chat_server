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

#include <string>
#include <map>
#include <algorithm>
using namespace std;

/* 用户在线列表 */
static map<uint32_t, struct bufferevent *> onlineMap;

static void read_cb(struct bufferevent *bev, void *arg);
static void write_cb(struct bufferevent *bev, void *arg);
static void event_cb(struct bufferevent *bev,short events, void *arg);
static void listener_cb(struct evconnlistener* listener, evutil_socket_t fd,
				struct sockaddr *addr, int len, void *ptr);
static void signal_cb(evutil_socket_t, short, void *);

string packet(const string &msgStr);
string unpacket(evbuffer *input);

#endif

