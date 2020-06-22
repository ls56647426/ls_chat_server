#include "FriendService.h"

FriendService::FriendService()
{

}

/* 查询某用户的所有好友 */
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

