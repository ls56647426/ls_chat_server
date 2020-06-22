#include "GroupDao.h"

/* c++ lib */
#include <iostream>

/* static */
//QCache<string, Group> GroupDao::groupCache;
//QCache<string, list<Group>> GroupDao::groupsCache;

GroupDao::GroupDao()
{

}

/* 根据id查找 */
Group *GroupDao::findOne(const uint32_t &id)
{
	/* 缓存 */
//	string key = string(*id);
//	if (groupCache.contains(key))
//		return groupCache.object(key);

	/* 组合sql语句 */
	string content = "select * from `group` where id = " + to_string(id);

	/* 获得查询结果 */
	MYSQL_RES* rec = ConnectionPool::runOne(content);

	/* 判空 */
	if(rec == nullptr)
		return nullptr;

	/* 将查询的结果存入Group类的对象中 */
	MYSQL_ROW row = mysql_fetch_row(rec);
	Group* group = new Group;
	group->setId(atoi(row[0]));
	group->setName(row[1]);

	/* 加入缓存 */
//	groupCache.insert(key, group);

	return group;
}

/* 根据自定义条件查找 */
Group *GroupDao::findOne(const Specification &spec)
{
//	if (groupCache.contains("findOne" + spec->getSqlWhere()))
//		return groupCache.object("findOne" + spec->getSqlWhere());

	/* 构建sql语句 */
	string content = "select * from `group` where " + spec.getSqlWhere();

	/* 获得查询结果 */
	MYSQL_RES* rec = ConnectionPool::runOne(content);

	/* 判空 */
	if(rec == nullptr)
		return nullptr;

	/* 将查询的结果存入Group类的对象中 */
	MYSQL_ROW row = mysql_fetch_row(rec);
	Group* group = new Group;
	group->setId(atoi(row[0]));
	group->setName(row[1]);

	/* 加入缓存 */
//	groupCache.insert(spec->getSqlWhere(), group);

	return group;
}

list<Group> GroupDao::findAll(const Specification &spec)
{
//	if (groupsCache.contains("findAll" + spec->getSqlWhere()))
//		return *groupsCache.object("findAll" + spec->getSqlWhere());

	list<Group> res;

	/* 构建sql语句 */
	string content = "select * from `group` " +
				(spec.getSqlWhere() == "" ? "" : "where " + spec.getSqlWhere());

	/* 获得查询结果 */
	MYSQL_RES* rec = ConnectionPool::runOne(content);

	/* 判空 */
	if(rec == nullptr)
		return res;

	/* 将查询的结果存入list<Group>链表中 */
	MYSQL_ROW row = NULL;
	while((row = mysql_fetch_row(rec)))
	{
		Group group;
		group.setId(atoi(row[0]));
		group.setName(row[1]);
		res.push_back(group);
	}

	/* 加入缓存 */
//	groupsCache.insert("findAll" + spec->getSqlWhere(), &res);

	return res;
}

/* 保存 */
void GroupDao::save(const Group *group)
{
	/* 先判断该群数据是否存在，以主键id来判断 */
	string content = "select * from `group` where id = " +
			to_string(group->getId());
	MYSQL_RES* rec = ConnectionPool::runOne(content);

	content.clear();
	if(rec == nullptr)
	{	/* 如果不存在，则insert */
		content = "insert into `group` values(null, " +
				Specification::tranString(group->getName()) + ")";
		ConnectionPool::runNo(content);
	}
	else
	{	/* 如果存在，则update */
		content = "update `group` set name = " +
			Specification::tranString(group->getName()) +
			" where id = " + to_string(group->getId()) + ")";
		ConnectionPool::runNo(content);
	}

	/* 清理缓存 */
//	groupCache.clear();
//	groupsCache.clear();
}

/* 删除 */
void GroupDao::del(const uint32_t &id)
{
	/* 先判断该群数据是否存在，以主键id来判断 */
	string content = "select * from `group` where id = " + to_string(id);
	MYSQL_RES* rec = ConnectionPool::runOne(content);

	/* 判空 */
	if(rec == nullptr)
	{
		cout << "无此群\n";
		return;
	}

	/* 删除该群数据 */
	content = "delete from `group` where id = " + to_string(id);
	ConnectionPool::runNo(content);

	/* 清理缓存 */
//	groupCache.clear();
//	groupsCache.clear();
}

