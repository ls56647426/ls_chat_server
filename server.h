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
using namespace std;

void read_cb(struct bufferevent *bev, void *arg);
void write_cb(struct bufferevent *bev, void *arg);
void event_cb(struct bufferevent *bev,short events, void *arg);
void listener_cb(struct evconnlistener* listener, evutil_socket_t fd,
				struct sockaddr *addr, int len, void *ptr);
void signal_cb(evutil_socket_t, short, void *);

string packet(const string &msgStr);
string unpacket(evbuffer *input);

#endif

