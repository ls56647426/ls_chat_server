#ifndef USERDAO_H
#define USERDAO_H

/* c++ lib */
#include <list>

#include "../pojo/User.h"
#include "../include/Specification.h"
#include "../include/ConnectionPool.h"

class UserDao
{
public:
	UserDao();

	/* 查找 */
	User* findOne(const uint32_t &id);
	User* findOne(const Specification &spec);

	list<User> findAll(const Specification &spec);

	/* 保存 */
	void save(const User *user);

	/* 删除 */
	void del(const uint32_t &id);

private:
	/* 单条记录缓存，key:"id"，value:"User" */
//	static QCache<string, User> userCache;
	/* 缓存多条记录，key:"方法名+参数"，value：user列表 */
//	static QCache<string, list<User>> usersCache;
};

#endif // USERDAO_H
