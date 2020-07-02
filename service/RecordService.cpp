/*
 * =====================================================================================
 *
 *       Filename:  RecordService.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/02/2020 02:50:01 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "RecordService.h"

RecordService::RecordService()
{

}

/* 查找某个用户的所有消息记录 */
list<Record> RecordService::findRecordByUserAndUser(const User &src, const User &dest)
{
	Specification spec;
	spec.setSqlWhere(
			Specification::Or(
				Specification::And(
					Specification::equal(
						"suid",
						to_string(src.getId())
						),
					Specification::equal(
						"duid",
						to_string(dest.getId())
						)
					),
				Specification::And(
					Specification::equal(
						"suid",
						to_string(dest.getId())
						),
					Specification::equal(
						"duid",
						to_string(src.getId())
						)
					)
				)
			);

	return rd.findAll(spec);
}

/* 查找某个群的所有消息记录 */
list<Record> RecordService::findRecordByGroup(const Group &group)
{
	Specification spec;
	spec.setSqlWhere(
			Specification::equal(
				"gid",
				to_string(group.getId())
				)
			);

	return rd.findAll(spec);
}

