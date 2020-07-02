/*
 * =====================================================================================
 *
 *       Filename:  MessageService.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/02/2020 09:45:33 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef MESSAGESERVICE_H
#define MESSAGESERVICE_H

#include "../dao/MessageDao.h"
#include "../dao/UserDao.h"

class MessageService
{
	public:
		MessageService();

		/* 查找user的所有通知 */
		list<Message> findMessageByUser(const User &user);

	private:
		MessageDao md;
};

#endif

