#include "FriendDao.h"

/* c++ lib */
#include <iostream>

/* static */
//QCache<string, Friend> FriendDao::friendCache;
//QCache<string, list<Friend>> FriendDao::friendsCache;

FriendDao::FriendDao()
{

}

/* 根据id查找 */
Friend *FriendDao::findOne(const uint32_t &id)
{
	/* 缓存 */
//	string key = string(*id);
//	if (friendCache.contains(key))
//		return friendCache.object(key);

	/* 组合sql语句 */
	string content = "select * from friend where id = " + to_string(id);

	/* 获得查询结果 */
	MYSQL_RES* rec = ConnectionPool::runOne(content);

	/* 判空 */
	if(rec == nullptr)
		return nullptr;

	/* 将查询的结果存入Friend类的对象中 */
	MYSQL_ROW row = mysql_fetch_row(rec);
	Friend* _friend = new Friend;
	_friend->setId(atoi(row[0]));
	_friend->setSuid(atoi(row[1]));
	_friend->setDuid(atoi(row[2]));
	_friend->setDate(row[3]);
	_friend->setPermission(atoi(row[4]));

	/* 加入缓存 */
//	friendCache.insert(key, _friend);

	return _friend;
}

/* 根据自定义条件查找 */
Friend *FriendDao::findOne(const Specification &spec)
{
//	if (friendCache.contains("findOne" + spec->getSqlWhere()))
//		return friendCache.object("findOne" + spec->getSqlWhere());

	/* 构建sql语句 */
	string content = "select * from friend where " + spec.getSqlWhere();

	/* 获得查询结果 */
	MYSQL_RES* rec = ConnectionPool::runOne(content);

	/* 判空 */
	if(rec == nullptr)
		return nullptr;

	/* 将查询的结果存入Friend类的对象中 */
	MYSQL_ROW row = mysql_fetch_row(rec);
	Friend* _friend = new Friend;
	_friend->setId(atoi(row[0]));
	_friend->setSuid(atoi(row[1]));
	_friend->setDuid(atoi(row[2]));
	_friend->setDate(row[3]);
	_friend->setPermission(atoi(row[4]));
	
	/* 加入缓存 */
//	friendCache.insert("findOne" + spec->getSqlWhere(), _friend);

	return _friend;
}

list<Friend> FriendDao::findAll(const Specification &spec)
{
//	if (friendsCache.contains("findAll" + spec->getSqlWhere()))
//		return *friendsCache.object("findAll" + spec->getSqlWhere());

	list<Friend> res;

	/* 构建sql语句 */
	string content = "select * from friend " +
				(spec.getSqlWhere() == "" ? "" : "where " + spec.getSqlWhere());

	/* 获得查询结果 */
	MYSQL_RES* rec = ConnectionPool::runOne(content);

	/* 将查询的结果存入list<Friend>链表中 */
	MYSQL_ROW row = NULL;
	while((row = mysql_fetch_row(rec)))
	{
		Friend _friend;
		_friend.setId(atoi(row[0]));
		_friend.setSuid(atoi(row[1]));
		_friend.setDuid(atoi(row[2]));
		_friend.setDate(row[3]);
		_friend.setPermission(atoi(row[4]));
		res.push_back(_friend);
	}

	/* 加入缓存 */
//	friendsCache.insert("findAll" + spec->getSqlWhere(), &res);

	return res;
}

/* 保存 */
void FriendDao::save(const Friend *_friend)
{
	/* 先判断该好友数据是否存在，以主键id来判断 */
	string content = "select * from friend where id = " +
		to_string(_friend->getId());
	MYSQL_RES* rec = ConnectionPool::runOne(content);

	content.clear();
	if(rec == nullptr)
	{	/* 如果不存在，则insert */
		content = "insert into friend values(null, " +
			to_string(_friend->getSuid()) + ", " +
			to_string(_friend->getDuid()) + ", " +
			Specification::tranString(_friend->getDate()) + ", " +
			to_string(_friend->getPermission()) + ")";
		ConnectionPool::runNo(content);
	}
	else
	{	/* 如果存在，则update */
		content = "update friend set suid = " +
			to_string(_friend->getSuid()) +
			", duid = " + to_string(_friend->getDuid()) +
			", date = " + Specification::tranString(_friend->getDate()) +
			", permission = " + to_string(_friend->getPermission()) +
			" where id = " + to_string(_friend->getId());
		ConnectionPool::runNo(content);
	}

	/* 清理缓存 */
//	friendCache.clear();
//	friendsCache.clear();
}

/* 删除 */
void FriendDao::del(const uint32_t &id)
{
	/* 先判断该好友数据是否存在，以主键id来判断 */
	string content = "select * from friend where id = " + to_string(id);
	MYSQL_RES* rec = ConnectionPool::runOne(content);

	/* 判空 */
	if(rec == nullptr)
	{
		cout << "无此好友\n";
		return;
	}

	/* 删除该好友数据 */
	content = "delete from friend where id = " + to_string(id);
	ConnectionPool::runNo(content);

	/* 清理缓存 */
//	friendCache.clear();
//	friendsCache.clear();
}

