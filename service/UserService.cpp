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

/* 通过username和password查找用户 */
User *UserService::findUserByUsernameAndPassword(const string &username, const string &password)
{
	Specification spec;
	spec.setSqlWhere(
			Specification::And(
				Specification::equal(
					"username",
					Specification::tranString(username)
					),
				Specification::equal(
					"password",
					Specification::tranString(password)
					)
				)
			);

	return ud.findOne(spec);
}

/* 将user存入数据库 */
uint32_t UserService::addUser(const User &user)
{
	Specification spec;
	User *u_tmp;

	/* 校验username */
	spec.setSqlWhere(
			Specification::equal(
				"username",
				Specification::tranString(user.getUsername())
				)
			);
	if(ud.findOne(spec))
	{
		printf("该用户已存在。\n");
		return MsgType::ERRNO_ALREADYEXIST;
	}

	/* 校验mobile */
	spec.setSqlWhere(
			Specification::equal(
				"mobile",
				Specification::tranString(user.getMobile())
				)
			);
	if(ud.findOne(spec))
	{
		printf("该手机号已被绑定。\n");
		return MsgType::ERRNO_MOBILE_ALREADYEXIST;
	}

	/* 校验邮箱 */
	spec.setSqlWhere(
			Specification::equal(
				"email",
				Specification::tranString(user.getEmail())
				)
			);
	u_tmp = ud.findOne(spec);
	if(u_tmp && u_tmp->getEmail() != "")
	{
		printf("该邮箱已被绑定。\n");
		return MsgType::ERRNO_EMAIL_ALREADYEXIST;
	}

	ud.save(&user);
	return MsgType::ERRNO_SUCCESS;
}

/* 修改用户数据 */
uint32_t UserService::updateUser(const User &user)
{
	Specification spec;
	User *u_tmp;

	/* 校验username */
	spec.setSqlWhere(
			Specification::equal(
				"username",
				Specification::tranString(user.getUsername())
				)
			);
	if(!ud.findOne(spec))
	{
		printf("该用户不存在。\n");
		return MsgType::ERRNO_INEXISTENCE;
	}

	/* 校验mobile */
	spec.setSqlWhere(
			Specification::And(
				Specification::equal(
					"mobile",
					Specification::tranString(user.getMobile())
					),
				Specification::notEqual(
					"id",
					to_string(user.getId())
					)
				)
			);
	if(ud.findOne(spec))
	{
		printf("该手机号已被绑定。\n");
		return MsgType::ERRNO_MOBILE_ALREADYEXIST;
	}

	/* 校验邮箱 */
	spec.setSqlWhere(
			Specification::And(
				Specification::equal(
					"email",
					Specification::tranString(user.getEmail())
					),
				Specification::notEqual(
					"id",
					to_string(user.getId())
					)
				)
			);
	u_tmp = ud.findOne(spec);
	if(u_tmp && u_tmp->getEmail() != "")
	{
		printf("该邮箱已被绑定。\n");
		return MsgType::ERRNO_EMAIL_ALREADYEXIST;
	}

	ud.save(&user);
	return MsgType::ERRNO_SUCCESS;
}

/* 通过username,password,mobile查找用户 */
User *UserService::findUserByUsernameAndPwdAndMobile(
		const string &username, const string &password, const string &mobile)
{
	Specification spec;

	list<string> list;
	list.push_back(
			Specification::equal(
				"username",
				Specification::tranString(username)
				)
			);
	list.push_back(
			Specification::equal(
				"password",
				Specification::tranString(password)
				)
			);
	list.push_back(
			Specification::equal(
				"mobile",
				Specification::tranString(mobile)
				)
			);
	spec.setSqlWhere(Specification::And(list));

	return ud.findOne(spec);
}

/* 通过username,mobile查找用户 */
User *UserService::findUserByUsernameAndMobile(const string &username, const string &mobile)
{
	Specification spec;

	list<string> list;
	list.push_back(
			Specification::equal(
				"username",
				Specification::tranString(username)
				)
			);
	list.push_back(
			Specification::equal(
				"mobile",
				Specification::tranString(mobile)
				)
			);
	spec.setSqlWhere(Specification::And(list));

	return ud.findOne(spec);
}

