/*
 * =====================================================================================
 *
 *       Filename:  RecordDao.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/02/2020 09:40:21 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef RECORDDAO_H
#define RECORDDAO_H

/* c++ lib */
#include <list>

#include "../pojo/Record.h"
#include "../include/Specification.h"
#include "../include/ConnectionPool.h"

class RecordDao
{
public:
	RecordDao();

	/* 查找 */
	Record* findOne(const uint32_t &id);
	Record* findOne(const Specification &spec);

	list<Record> findAll(const Specification &spec);

	/* 保存 */
	void save(const Record *record);

	/* 删除 */
	void del(const uint32_t &id);

private:
	/* 单条记录缓存，key:"id"，value:"Record" */
//	static QCache<string, Record> recordCache;
	/* 缓存多条记录，key:"方法名+参数"，value：record列表 */
//	static QCache<string, list<Record>> recordsCache;
};

#endif

