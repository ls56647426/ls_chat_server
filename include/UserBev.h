/*
 * =====================================================================================
 *
 *       Filename:  UserBev.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/29/2020 12:12:51 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef _USERBEV_H_
#define _USERBEV_H_

/* c lib */
#include <stdint.h>

#include <event2/bufferevent.h>

class UserBev
{
	uint32_t getId() const;
	void setId(const uint32_t &value);

	struct bufferevent *getBev() const;
	void setBev(const struct bufferevent *&value);

	private:
		uint32_t id;
		struct bufferevent *bev;
};

#endif

