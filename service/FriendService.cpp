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
		int uid = (_friend.getSuid() == user.getId() ? _friend.getDuid() :
				_friend.getSuid());
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
				Specification::equal("suid", to_string(user.getId())),
				Specification::equal("duid", to_string(user.getId()))
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
	Specification spec;
	spec.setSqlWhere(
			Specification::Or(
				Specification::And(
					Specification::equal("suid", to_string(uid1)),
					Specification::equal("duid", to_string(uid2))
					),
				Specification::And(
					Specification::equal("suid", to_string(uid2)),
					Specification::equal("duid", to_string(uid1))
					)
			)
			);

	return fd.findOne(spec);
}

/* 加好友 */
void FriendService::addFriend(Friend _friend)
{
	fd.save(&_friend);
}

