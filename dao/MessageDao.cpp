/*
 * =====================================================================================
 *
 *       Filename:  MessageDao.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/02/2020 09:09:55 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "MessageDao.h"

#include <iostream>

MessageDao::MessageDao()
{

}

/* 查找 */
Message* MessageDao::findOne(const uint32_t &id)
{
	/* 组合sql语句 */
	string content = "select * from `message` where id = " + to_string(id);

	/* 获得查询结果 */
	MYSQL_RES* rec = ConnectionPool::runOne(content);

	/* 判空 */
	if(rec == nullptr)
		return nullptr;

	/* 将查询的结果存入Message类的对象中 */
	MYSQL_ROW row = mysql_fetch_row(rec);
	Message* message = new Message();
	message->setId(atoi(row[0]));
	message->setType(atoi(row[1]));
	message->setUid(atoi(row[2]));
	message->setSrc(row[3]);
	message->setContent(row[4]);
	message->setDate(row[5]);
	message->setStatus(atoi(row[6]));

	return message;
}
Message* MessageDao::findOne(const Specification &spec)
{
	/* 组合sql语句 */
	string content = "select * from `message` where " + spec.getSqlWhere();

	/* 获得查询结果 */
	MYSQL_RES* rec = ConnectionPool::runOne(content);

	/* 判空 */
	if(rec == nullptr)
		return nullptr;

	/* 将查询的结果存入Message类的对象中 */
	MYSQL_ROW row = mysql_fetch_row(rec);
	Message* message = new Message();
	message->setId(atoi(row[0]));
	message->setType(atoi(row[1]));
	message->setUid(atoi(row[2]));
	message->setSrc(row[3]);
	message->setContent(row[4]);
	message->setDate(row[5]);
	message->setStatus(atoi(row[6]));

	return message;

}

list<Message> MessageDao::findAll(const Specification &spec)
{
	list<Message> res;

	/* 构建sql语句 */
	string content = "select * from `message` " +
		(spec.getSqlWhere() == "" ? "" : "where " + spec.getSqlWhere());

	/* 获得查询结果 */
	MYSQL_RES* rec = ConnectionPool::runOne(content);

	/* 判空 */
	if(rec == nullptr)
		return res;

	/* 将查询的结果存入list<Message>链表中 */
	MYSQL_ROW row = NULL;
	while((row = mysql_fetch_row(rec)))
	{
		Message message;
		message.setId(atoi(row[0]));
		message.setType(atoi(row[1]));
		message.setUid(atoi(row[2]));
		message.setSrc(row[3]);
		message.setContent(row[4]);
		message.setDate(row[5]);
		message.setStatus(atoi(row[6]));
		res.push_back(message);
	}

	return res;
}

/* 保存 */
void MessageDao::save(const Message *message)
{
	/* 先判断该用户数据是否存在，以主键id来判断 */
	string content = "select * from `message` where id = " + to_string(message->getId());
	MYSQL_RES* rec = ConnectionPool::runOne(content);

	content.clear();
	if(rec == nullptr)
	{	/* 如果不存在，则insert */
		content = "insert into `message` values(null, " +
			to_string(message->getType()) + ", " +
			to_string(message->getUid()) + ", " +
			Specification::tranString(message->getSrc()) + ", " +
			Specification::tranString(message->getContent()) + ", " +
			Specification::tranString(message->getDate()) + ", " +
			to_string(message->getStatus()) + ")";
		ConnectionPool::runNo(content);
	}
	else
	{	/* 如果存在，则update */
		content = "update `message` set type = " +
			to_string(message->getType()) + ", uid = " +
			to_string(message->getUid()) + ", src = " +
			Specification::tranString(message->getSrc()) + ", content = " +
			Specification::tranString(message->getContent()) + ", date = " +
			Specification::tranString(message->getDate()) + ", status = " +
			to_string(message->getStatus()) +
			" where id = " + to_string(message->getId());
		ConnectionPool::runNo(content);
	}
}

/* 删除 */
void MessageDao::del(const uint32_t &id)
{
	/* 先判断该用户数据是否存在，以主键id来判断 */
	string content = "select * from `message` where id = " + to_string(id);
	MYSQL_RES* rec = ConnectionPool::runOne(content);

	/* 判空 */
	if(rec == nullptr)
	{
		cout << "无此记录\n";
		return;
	}

	/* 删除该记录数据 */
	content.clear();
	content = "delete from `message` where id = " + to_string(id);
	ConnectionPool::runNo(content);
}

