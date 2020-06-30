#ifndef FRIENDSERVICE_H
#define FRIENDSERVICE_H

#include "../dao/FriendDao.h"
#include "../dao/UserDao.h"

class FriendService
{
public:
	FriendService();

	/* 查询某用户的所有好友 */
	list<User> findUserAllByUser(const User &user);
	list<Friend> findAllByUser(const User &user);

	/* 查找好友 */
	Friend *findFriend(const User &user1, const User &user2);

	/* 根据Uid查找好友 */
	Friend *findFriendByUid(uint32_t uid1, uint32_t uid2);

	/* 加好友 */
	void addFriend(Friend _friend);

private:
	FriendDao fd;
	UserDao ud;
};

#endif // FRIENDSERVICE_H

