#include "UserService.h"

UserService::UserService()
{

}

/* 通过id查找用户 */
User *UserService::findUserById(const uint32_t &id)
{
	return ud.findOne(id);
}

/* 通过username查找用户 */
User *UserService::findUserByUsername(const string &username)
{
	Specification spec;
	spec.setSqlWhere(
				Specification::equal(
					"username",
					Specification::tranString(username)
					)
				);

	return ud.findOne(spec);
}

