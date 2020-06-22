#include "UserGroupMapDao.h"

/* c++ lib */
#include <iostream>

/* static */
//QCache<string, UserGroupMap> UserGroupMapDao::userGroupMapCache;
//QCache<string, list<UserGroupMap>> UserGroupMapDao::userGroupMapsCache;

UserGroupMapDao::UserGroupMapDao()
{

}

/* 根据id查找 */
UserGroupMap *UserGroupMapDao::findOne(const uint32_t &id)
{
	/* 缓存 */
//	string key = string(*id);
//	if (userGroupMapCache.contains(key))
//		return userGroupMapCache.object(key);

	/* 组合sql语句 */
	string content = "select * from user_group_map where id = " + to_string(id);

	/* 获得查询结果 */
	MYSQL_RES* rec = ConnectionPool::runOne(content);

	/* 判空 */
	if(rec == nullptr)
		return nullptr;

	/* 将查询的结果存入Friend类的对象中 */
	MYSQL_ROW row = mysql_fetch_row(rec);
	UserGroupMap* userGroupMap = new UserGroupMap;
	userGroupMap->setId(atoi(row[0]));
	userGroupMap->setUid(atoi(row[1]));
	userGroupMap->setGid(atoi(row[2]));
	userGroupMap->setStatus(atoi(row[3]));
	userGroupMap->setPermission(atoi(row[4]));

	/* 加入缓存 */
//	userGroupMapCache.insert(key, userGroupMap);

	return userGroupMap;
}

/* 根据自定义条件查找 */
UserGroupMap *UserGroupMapDao::findOne(const Specification &spec)
{
//	if (userGroupMapCache.contains(spec->getSqlWhere()))
//		return userGroupMapCache.object(spec->getSqlWhere());

	/* 构建sql语句 */
	string content = "select * from user_group_map where " + spec.getSqlWhere();

	/* 获得查询结果 */
	MYSQL_RES* rec = ConnectionPool::runOne(content);

	/* 判空 */
	if(rec == nullptr)
		return nullptr;

	/* 将查询的结果存入Group类的对象中 */
	MYSQL_ROW row = mysql_fetch_row(rec);
	UserGroupMap* userGroupMap = new UserGroupMap;
	userGroupMap->setId(atoi(row[0]));
	userGroupMap->setUid(atoi(row[1]));
	userGroupMap->setGid(atoi(row[2]));
	userGroupMap->setStatus(atoi(row[3]));
	userGroupMap->setPermission(atoi(row[4]));

	/* 加入缓存 */
//	userGroupMapCache.insert(spec->getSqlWhere(), userGroupMap);

	return userGroupMap;
}

list<UserGroupMap> UserGroupMapDao::findAll(const Specification &spec)
{
//	if (userGroupMapsCache.contains("findAll" + spec->getSqlWhere()))
//		return *userGroupMapsCache.object("findAll" + spec->getSqlWhere());

	list<UserGroupMap> res;

	/* 构建sql语句 */
	string content = "select * from user_group_map " +
				(spec.getSqlWhere() == "" ? "" : "where " + spec.getSqlWhere());

	/* 获得查询结果 */
	MYSQL_RES* rec = ConnectionPool::runOne(content);

	/* 将查询的结果存入list<Group>链表中 */
	MYSQL_ROW row = NULL;
	while((row = mysql_fetch_row(rec)))
	{
		UserGroupMap userGroupMap;
		userGroupMap.setId(atoi(row[0]));
		userGroupMap.setUid(atoi(row[1]));
		userGroupMap.setGid(atoi(row[2]));
		userGroupMap.setStatus(atoi(row[3]));
		userGroupMap.setPermission(atoi(row[4]));
		res.push_back(userGroupMap);
	}

	/* 加入缓存 */
//	userGroupMapsCache.insert("findAll" + spec->getSqlWhere(), &res);

	return res;
}

/* 保存 */
void UserGroupMapDao::save(const UserGroupMap *userGroupMap)
{
	/* 先判断该 群/成员 数据是否存在，以主键id来判断 */
	string content = "select * from user_group_map where id = " + userGroupMap->getId();
	MYSQL_RES* rec = ConnectionPool::runOne(content);

	content.clear();
	if(rec == nullptr)
	{	/* 如果不存在，则insert */
		content = "insert into user_group_map values(null, " +
			to_string(userGroupMap->getUid()) + ", " +
			to_string(userGroupMap->getGid()) + ", " +
			to_string(userGroupMap->getStatus()) + ", " +
			to_string(userGroupMap->getPermission()) + ")";
		ConnectionPool::runNo(content);
	}
	else
	{	/* 如果存在，则update */
		content = "update user_group_map set uid = " +
				to_string(userGroupMap->getUid()) +
				", gid = " + to_string(userGroupMap->getGid()) +
				", status = " + to_string(userGroupMap->getStatus()) +
				", permission = " + to_string(userGroupMap->getPermission()) +
				" where id = " + to_string(userGroupMap->getId());
		ConnectionPool::runNo(content);
	}

	/* 清理缓存 */
//	userGroupMapCache.clear();
//	userGroupMapsCache.clear();
}

/* 删除 */
void UserGroupMapDao::del(const uint32_t &id)
{
	/* 先判断该 群/成员 数据是否存在，以主键id来判断 */
	string content = "select * from user_group_map where id = " + to_string(id);
	MYSQL_RES* rec = ConnectionPool::runOne(content);

	/* 判空 */
	if(rec == nullptr)
	{
		cout << "无此 群/成员\n";
		return;
	}

	/* 删除该 群/成员 数据 */
	content = "delete from user_group_map where id = " + to_string(id);
	ConnectionPool::runNo(content);

	/* 清理缓存 */
//	userGroupMapCache.clear();
//	userGroupMapsCache.clear();
}

