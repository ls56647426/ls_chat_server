#include "UserGroupMapService.h"

UserGroupMapService::UserGroupMapService()
{

}

list<UserGroupMap> UserGroupMapService::findAllByUser(const User &user)
{
	Specification spec;
	spec.setSqlWhere(
			Specification::equal(
				"uid",
				to_string(user.getId()))
			);

	return ugmd.findAll(spec);
}

