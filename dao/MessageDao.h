/*
 * =====================================================================================
 *
 *       Filename:  MessageDao.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/02/2020 09:10:03 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef MESSAGEDAO_H
#define MESSAGEDAO_H

/* c++ lib */
#include <list>

#include "../pojo/Message.h"
#include "../include/Specification.h"
#include "../include/ConnectionPool.h"

class MessageDao
{
public:
	MessageDao();

	/* 查找 */
	Message* findOne(const uint32_t &id);
	Message* findOne(const Specification &spec);

	list<Message> findAll(const Specification &spec);

	/* 保存 */
	void save(const Message *message);

	/* 删除 */
	void del(const uint32_t &id);

private:
	/* 单条记录缓存，key:"id"，value:"Message" */
//	static QCache<string, Message> messageCache;
	/* 缓存多条记录，key:"方法名+参数"，value：message列表 */
//	static QCache<string, list<Message>> messagesCache;
};

#endif

