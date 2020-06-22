#ifndef USERSERVICE_H
#define USERSERVICE_H

#include "../dao/UserDao.h"

class UserService
{
public:
	UserService();

	/* 通过id查找用户 */
	User *findUserById(const uint32_t &id);

	/* 通过username查找用户 */
	User *findUserByUsername(const string &username);

private:
	UserDao ud;
};

#endif // USERSERVICE_H
