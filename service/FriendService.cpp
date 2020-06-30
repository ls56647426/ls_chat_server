#include "FriendService.h"

FriendService::FriendService()
{

}

/* 查询某用户的所有好友 */
list<User> FriendService::findUserAllByUser(const User &user)
{
	list<User> res;
	list<Friend> friList = findAllByUser(user);
	
	for(Friend _friend : friList)
	{
		int uid = (_friend.getUid1() == user.getId() ? _friend.getUid2() :
				_friend.getUid1());
		User *user = ud.findOne(uid);
		res.push_back(*user);
		delete user;
	}
	
	return res;
}

list<Friend> FriendService::findAllByUser(const User &user)
{
	Specification spec;
	spec.setSqlWhere(
			Specification::Or(
				Specification::equal("uid1", to_string(user.getId())),
				Specification::equal("uid2", to_string(user.getId()))
				)
			);

	return fd.findAll(spec);
}

/* 查找好友 */
Friend *FriendService::findFriend(const User &user1, const User &user2)
{
	return findFriendByUid(user1.getId(), user2.getId());
}

/* 根据Uid查找好友 */
Friend *FriendService::findFriendByUid(uint32_t uid1, uint32_t uid2)
{
	/* 保证uid < uid2 */
	if(uid1 > uid2) uid1 ^= uid2 ^= uid1 ^= uid2;
	Specification spec;
	spec.setSqlWhere(
			Specification::And(
				Specification::equal("uid1", to_string(uid1)),
				Specification::equal("uid2", to_string(uid2))
				)
			);

	return fd.findOne(spec);
}

/* 加好友 */
void FriendService::addFriend(Friend _friend)
{
	/* 保证uid1 < uid2 */
	uint32_t uid1 = _friend.getUid1(), uid2 = _friend.getUid2();
	if(uid1 > uid2)
	{
		_friend.setUid1(uid2);
		_friend.setUid2(uid1);
	}

	fd.save(&_friend);
}

