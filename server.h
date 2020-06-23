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

void read_cb(struct bufferevent *bev, void *arg);
void write_cb(struct bufferevent *bev, void *arg);
void event_cb(struct bufferevent *bev,short events, void *arg);
void listener_cb(struct evconnlistener* listener, evutil_socket_t fd,
				struct sockaddr *addr, int len, void *ptr);
void signal_cb(evutil_socket_t, short, void *);

#endif

