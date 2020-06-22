#ifndef MSG_H
#define MSG_H

#include "../pojo/User.h"
#include "../pojo/Group.h"

/**
 * @brief [The MsgType enum]
 * Msg_Register：					注册
 * Msg_Login：						登录
 * Msg_SendMsg：						发送消息
 * Msg_Logout：						退出
 * Msg_TranFile：					发送文件
 * COMMAND_GET_ONLINEUSER：			获取好友在线用户列表
 * COMMAND_GROUP_BANUSERPOST：		群内禁言
 * COMMAND_GROUP_DELETEUSER：		踢人
 * COMMAND_FILE_UPLOAD：				上传文件
 * COMMAND_FILE_DOWNLOAD：			下载文件
 * COMMAND_CREATE_GROUP：			创建群
 * COMMAND_APPLY_ADD_GROUP：			申请加群
 * COMMAND_ADMINIST_ADD_GROUP：		管理加群申请
 * COMMAND_GET_GROUP_FILE：			获取群文件
 * COMMAND_ADD_USER：				加好友
 * COMMAND_GET_GROUP_ONLINEUSER：	获取群成员在线列表
 * COMMAND_INTO_GROUP：				进群聊天
 * COMMAND_INTO_CHATUSER：			进入私聊
 * COMMAND_FILE_UPLOAD_ING：			正在上传群文件
 * COMMAND_EXIT_CHATGROUP：			离开了群聊
 * ERRNO_SUCCESS：					成功
 * ERRNO_ALREADYEXIST：				该用户已存在
 * ERRNO_INEXISTENCE：				该用户不存在
 * ERRNO_NOTFOUND：					未找到该用户
 * ERRNO_BEOFFLINE：					被挤掉了，下线
 * ERRNO_GROUP_ALREADYEXIST：		该群已存在
 * ERRNO_GROUP_INEXISTENCE：			该群不存在
 * ERRNO_ADDUSER_NOTFOUND：			加好友，没找到该用户
 */
enum MsgType
{
	Msg_Register, Msg_Login, Msg_SendMsg, Msg_Logout, Msg_TranFile,

	COMMAND_GET_ONLINEUSER, COMMAND_GROUP_BANUSERPOST, COMMAND_GROUP_DELETEUSER,
	COMMAND_FILE_UPLOAD, COMMAND_FILE_DOWNLOAD, COMMAND_CREATE_GROUP,
	COMMAND_APPLY_ADD_GROUP, COMMAND_ADMINIST_ADD_GROUP, COMMAND_GET_GROUP_FILE,
	COMMAND_ADD_USER, COMMAND_GET_GROUP_ONLINEUSER, COMMAND_INTO_GROUP,
	COMMAND_INTO_CHATUSER, COMMAND_FILE_UPLOAD_ING, COMMAND_EXIT_CHATGROUP,

	ERRNO_SUCCESS, ERRNO_ALREADYEXIST, ERRNO_INEXISTENCE, ERRNO_NOTFOUND,
	ERRNO_BEOFFLINE, ERRNO_GROUP_ALREADYEXIST, ERRNO_GROUP_INEXISTENCE,
	ERRNO_ADDUSER_NOTFOUND
};

const int MSGINFO_MAX_LEN = 256;

class MsgInfo
{
public:
	MsgInfo();

	string getInfo() const;
	void setInfo(const string &value);

	string toString() const;

private:
	string info;
	//	FileInfo file_info;
	//	TranFile file_data;
};

class Msg
{
public:
	Msg();

	uint32_t getType() const;
	void setType(const uint32_t &value);

	Group getGroup() const;
	void setGroup(const Group &value);

	User getSrc() const;
	void setSrc(const User &value);

	User getDest() const;
	void setDest(const User &value);

	MsgInfo getInfo() const;
	void setInfo(const MsgInfo &value);

	string toString() const;

private:
	uint32_t type;
	Group group;
	User src;
	User dest;
	MsgInfo info;
};

#endif // MSG_H
