#ifndef FRIENDSERVICE_H
#define FRIENDSERVICE_H

#include "../dao/FriendDao.h"
#include "../dao/UserDao.h"

class FriendService
{
public:
	FriendService();

	/* 查询某用户的所有好友 */
	list<Friend> findAllByUser(const User &user);

private:
	FriendDao fd;
};

#endif // FRIENDSERVICE_H

