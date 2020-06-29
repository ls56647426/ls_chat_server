#ifndef USERSERVICE_H
#define USERSERVICE_H

#include "../dao/UserDao.h"
#include "../include/Msg.h"

class UserService
{
public:
	UserService();

	/* 通过id查找用户 */
	User *findUserById(const uint32_t &id);

	/* 通过username查找用户 */
	User *findUserByUsername(const string &username);

	/* 通过username和password查找用户 */
	User *findUserByUsernameAndPassword(const string &username, const string &password);

	/* 将user存入数据库 */
	uint32_t addUser(const User &user);

	/* 修改用户数据 */
	uint32_t updateUser(const User &user);

private:
	UserDao ud;
};

#endif // USERSERVICE_H

