/*
 * =====================================================================================
 *
 *       Filename:  RecordDao.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/02/2020 09:43:10 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "RecordDao.h"

#include <iostream>

RecordDao::RecordDao()
{

}

/* 查找 */
Record* RecordDao::findOne(const uint32_t &id)
{
	/* 组合sql语句 */
	string content = "select * from `record` where id = " + to_string(id);

	/* 获得查询结果 */
	MYSQL_RES* rec = ConnectionPool::runOne(content);

	/* 判空 */
	if(rec == nullptr)
		return nullptr;

	/* 将查询的结果存入Record类的对象中 */
	MYSQL_ROW row = mysql_fetch_row(rec);
	Record* record = new Record();
	record->setId(atoi(row[0]));
	record->setGid(atoi(row[1]));
	record->setSuid(atoi(row[2]));
	record->setDuid(atoi(row[3]));
	record->setContent(row[4]);
	record->setDate(row[5]);

	return record;
}
Record* RecordDao::findOne(const Specification &spec)
{
	/* 组合sql语句 */
	string content = "select * from `record` where " + spec.getSqlWhere();

	/* 获得查询结果 */
	MYSQL_RES* rec = ConnectionPool::runOne(content);

	/* 判空 */
	if(rec == nullptr)
		return nullptr;

	/* 将查询的结果存入Record类的对象中 */
	MYSQL_ROW row = mysql_fetch_row(rec);
	Record* record = new Record();
	record->setId(atoi(row[0]));
	record->setGid(atoi(row[1]));
	record->setSuid(atoi(row[2]));
	record->setDuid(atoi(row[3]));
	record->setContent(row[4]);
	record->setDate(row[5]);

	return record;
}

list<Record> RecordDao::findAll(const Specification &spec)
{
	list<Record> res;

	/* 构建sql语句 */
	string content = "select * from record " +
		(spec.getSqlWhere() == "" ? "" : "where " + spec.getSqlWhere());

	/* 获得查询结果 */
	MYSQL_RES* rec = ConnectionPool::runOne(content);

	/* 判空 */
	if(rec == nullptr)
		return res;

	/* 将查询的结果存入list<Record>链表中 */
	MYSQL_ROW row = NULL;
	while((row = mysql_fetch_row(rec)))
	{
		Record record;
		record.setId(atoi(row[0]));
		record.setGid(atoi(row[1]));
		record.setSuid(atoi(row[2]));
		record.setDuid(atoi(row[3]));
		record.setContent(row[4]);
		record.setDate(row[5]);
		res.push_back(record);
	}

	return res;
}

/* 保存 */
void RecordDao::save(const Record *record)
{
	/* 先判断该用户数据是否存在，以主键id来判断 */
	string content = "select * from record where id = " + to_string(record->getId());
	MYSQL_RES* rec = ConnectionPool::runOne(content);

	content.clear();
	if(rec == nullptr)
	{	/* 如果不存在，则insert */
		content = "insert into record values(null, " +
			to_string(record->getGid()) + ", " +
			to_string(record->getSuid()) + ", " +
			to_string(record->getDuid()) + ", " +
			Specification::tranString(record->getContent()) + ", " +
			Specification::tranString(record->getDate()) + ")";
		ConnectionPool::runNo(content);
	}
	else
	{	/* 如果存在，则update */
		content = "update record set gid = " +
			to_string(record->getGid()) + ", suid = " +
			to_string(record->getSuid()) + ", duid = " +
			to_string(record->getDuid()) + ", content = " +
			Specification::tranString(record->getContent()) + ", date" +
			Specification::tranString(record->getDate()) +
			" where id = " + to_string(record->getId());
		ConnectionPool::runNo(content);
	}
}

/* 删除 */
void RecordDao::del(const uint32_t &id)
{
	/* 先判断该用户数据是否存在，以主键id来判断 */
	string content = "select * from record where id = " + to_string(id);
	MYSQL_RES* rec = ConnectionPool::runOne(content);

	/* 判空 */
	if(rec == nullptr)
	{
		cout << "无此记录\n";
		return;
	}

	/* 删除该记录数据 */
	content.clear();
	content = "delete from record where id = " + to_string(id);
	ConnectionPool::runNo(content);
}

