/*
 * =====================================================================================
 *
 *       Filename:  MessageService.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/02/2020 09:45:29 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "MessageService.h"

MessageService::MessageService()
{

}

/* 查找user的所有通知 */
list<Message> MessageService::findMessageByUser(const User &user)
{
	Specification spec;
	spec.setSqlWhere(
			Specification::equal(
				"uid",
				to_string(user.getId())
				)
			);

	return md.findAll(spec);
}

