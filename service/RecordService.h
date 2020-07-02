/*
 * =====================================================================================
 *
 *       Filename:  RecordService.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/02/2020 02:50:45 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef RECORDSERVICE_H
#define RECORDSERVICE_H

#include "../dao/RecordDao.h"
#include "../dao/UserDao.h"
#include "../dao/GroupDao.h"

class RecordService
{
	public:
		RecordService();

		/* 查找user和user的所有消息记录 */
		list<Record> findRecordByUserAndUser(const User &src, const User &dest);

		/* 查找某个群的所有消息记录 */
		list<Record> findRecordByGroup(const Group &group);

	private:
		RecordDao rd;
};

#endif


