#include "UserDao.h"

#include <iostream>

/* static */
//map<string, User> UserDao::userCache;
//map<string, list<User>> UserDao::usersCache;

UserDao::UserDao()
{

}

/* 根据id查找 */
User *UserDao::findOne(const uint32_t &id)
{
	/* 缓存 */
//	string key = "findOne" + string(*id);
//	if (userCache.contains(key))
//		return userCache.object(key);

	/* 组合sql语句 */
	string content = "select * from user where id = " + to_string(id);

	/* 获得查询结果 */
	MYSQL_RES* rec = ConnectionPool::runOne(content);

	/* 判空 */
	if(rec == nullptr)
		return nullptr;

	/* 将查询的结果存入User类的对象中 */
	MYSQL_ROW row = mysql_fetch_row(rec);
	User* user = new User();
	user->setId(atoi(row[0]));
	user->setUsername(row[1]);
	user->setPassword(row[2]);
        user->setHead_portrait(row[3]);
        user->setNickname(row[4]);
        user->setSignature(row[5]);
        user->setSex(row[6]);
        user->setBirthday(row[7]);
        user->setLocation(row[8]);
        user->setProfession(row[9]);
        user->setMobile(row[10]);
        user->setEmail(row[11]);
        user->setStatus(atoi(row[12]));

	/* 加入缓存 */
//	userCache.insert(key, user);

	return user;
}

/* 根据自定义条件查找 */
User *UserDao::findOne(const Specification &spec)
{
//	if (userCache.contains("findOne" + spec->getSqlWhere()))
//		return userCache.object("findOne" + spec->getSqlWhere());

	/* 构建sql语句 */
	string content = "select * from user where " + spec.getSqlWhere();

	/* 获得查询结果 */
	MYSQL_RES* rec = ConnectionPool::runOne(content);

	/* 判空 */
	if(rec == nullptr)
		return nullptr;

	/* 将查询的结果存入User类的对象中 */
	MYSQL_ROW row = mysql_fetch_row(rec);
	User* user = new User();
        user->setId(atoi(row[0]));
        user->setUsername(row[1]);
        user->setPassword(row[2]);
        user->setHead_portrait(row[3]);
        user->setNickname(row[4]);
        user->setSignature(row[5]);
        user->setSex(row[6]);
        user->setBirthday(row[7]);
        user->setLocation(row[8]);
        user->setProfession(row[9]);
        user->setMobile(row[10]);
        user->setEmail(row[11]);
        user->setStatus(atoi(row[12]));


	/* 加入缓存 */
//	userCache.insert("findOne" + spec->getSqlWhere(), user);

	return user;
}

list<User> UserDao::findAll(const Specification &spec)
{
//	if (usersCache.contains("findAll" + spec->getSqlWhere()))
//		return *usersCache.object("findAll" + spec->getSqlWhere());

	list<User> res;

	/* 构建sql语句 */
	string content = "select * from user " +
		(spec.getSqlWhere() == "" ? "" : "where " + spec.getSqlWhere());

	/* 获得查询结果 */
	MYSQL_RES* rec = ConnectionPool::runOne(content);

	/* 判空 */
	if(rec == nullptr)
		return res;

	/* 将查询的结果存入list<User>链表中 */
	MYSQL_ROW row = NULL;
	while((row = mysql_fetch_row(rec)))
	{
		User user;
                user.setId(atoi(row[0]));
                user.setUsername(row[1]);
                user.setPassword(row[2]);
                user.setHead_portrait(row[3]);
                user.setNickname(row[4]);
                user.setSignature(row[5]);
                user.setSex(row[6]);
                user.setBirthday(row[7]);
                user.setLocation(row[8]);
                user.setProfession(row[9]);
                user.setMobile(row[10]);
                user.setEmail(row[11]);
                user.setStatus(atoi(row[12]));
		res.push_back(user);
	}

	/* 加入缓存 */
//	usersCache.insert("findAll" + spec->getSqlWhere(), &res);

	return res;
}

/* 保存 */
void UserDao::save(const User *user)
{
	/* 先判断该用户数据是否存在，以主键id来判断 */
	string content = "select * from user where id = " + to_string(user->getId());
	MYSQL_RES* rec = ConnectionPool::runOne(content);

	content.clear();
	if(rec == nullptr)
	{	/* 如果不存在，则insert */
		content = "insert into user values(null, " +
			Specification::tranString(user->getUsername()) +
			", " + Specification::tranString(user->getPassword()) +
                        ", " + Specification::tranString(user->getHead_portrait()) +
                        ", " + Specification::tranString(user->getNickname()) +
                        ", " + Specification::tranString(user->getSignature()) +
                        ", " + Specification::tranString(user->getSex()) +
                        ", " + Specification::tranString(user->getBirthday()) +
                        ", " + Specification::tranString(user->getLocation()) +
                        ", " + Specification::tranString(user->getProfession()) +
                        ", " + Specification::tranString(user->getMobile()) +
                        ", " + Specification::tranString(user->getEmail()) +
			", " + to_string(user->getStatus()) + ")";
		ConnectionPool::runNo(content);
	}
	else
	{	/* 如果存在，则update */
		content = "update user set username = " +
			Specification::tranString(user->getUsername()) +
			", password = " + Specification::tranString(user->getPassword()) +
                        ", head_portrait = " + Specification::tranString(user->getHead_portrait()) +
                        ", nickname = " + Specification::tranString(user->getNickname()) +
                        ", signature = " + Specification::tranString(user->getSignature()) +
                        ", sex = " + Specification::tranString(user->getSex()) +
                        ", birthday = " + Specification::tranString(user->getBirthday()) +
                        ", location = " + Specification::tranString(user->getLocation()) +
                        ", profession = " + Specification::tranString(user->getProfession()) +
			", mobile = " + Specification::tranString(user->getMobile()) +
                        ", email = " + Specification::tranString(user->getEmail()) +
			", status = " + to_string(user->getStatus()) +
			" where id = " + to_string(user->getId());
		ConnectionPool::runNo(content);
	}

	/* 清理缓存 */
//	userCache.clear();
//	usersCache.clear();
}

/* 删除 */
void UserDao::del(const uint32_t &id)
{
	/* 先判断该用户数据是否存在，以主键id来判断 */
	string content = "select * from user where id = " + to_string(id);
	MYSQL_RES* rec = ConnectionPool::runOne(content);

	/* 判空 */
	if(rec == nullptr)
	{
		cout << "无此用户\n";
		return;
	}

	/* 删除该用户数据 */
	content.clear();
	content = "delete from user where id = " + to_string(id);
	ConnectionPool::runNo(content);

	/* 清理缓存 */
//	userCache.clear();
//	usersCache.clear();
}

