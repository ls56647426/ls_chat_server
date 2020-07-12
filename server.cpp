/*
 * =====================================================================================
 *
 *       Filename:  server.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/19/2020 11:27:31 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

/* c std lib */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

/* unix lib */
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <pthread.h>
#include <signal.h>
#include <sys/param.h>

/* c++ lib */
#include <iostream>

/* third-party lib */
#include <zlib.h>
#include <json/json.h>

/* custom lib */
#include "server.h"
#include "service/UserService.h"
#include "service/FriendService.h"

#define SERV_PORT 5664
#define UDP_SERV_PORT 7426
#define SERV_IP "112.124.19.14"

UserService us;
FriendService fs;

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  服务器端主函数
 * =====================================================================================
 */
int main ( int argc, char *argv[] )
{
	int pid;
	/* 启动守护进程 */
	if(argc == 2 && !strcmp(argv[1], "-d"))
	{
		pid = fork();
		if(pid > 0)
			exit(0);
		
		if(pid < 0)
			exit(-1);

		setsid();

		chdir("/root/sources/git/ls_chat_server/release");

		umask(0);

		for(int i = 0; i < NOFILE; i++)
			close(i);
	}

	/* 初始化服务器地址结构 */
	struct sockaddr_in serv_addr;
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	//	inet_pton(AF_INET, SERV_IP, &serv_addr.sin_addr.s_addr);
	serv_addr.sin_port = htons(SERV_PORT);

	//创建event_base
	struct event_base *base;
	base = event_base_new();

	//创建监听器
	struct evconnlistener *listener;
	listener = evconnlistener_new_bind(base, listener_cb, base, 
			LEV_OPT_CLOSE_ON_FREE | LEV_OPT_REUSEABLE, -1, 
			(struct sockaddr*)&serv_addr, sizeof(serv_addr));

	/* 注册普通的信号事件 */
	struct event *signal_event = evsignal_new(base, SIGINT, signal_cb, base);
	if(!signal_event || event_add(signal_event, NULL) < 0)
	{
		fprintf(stderr, "信号事件注册失败!\n");
		exit(1);
	}

	//启动循环监听
	event_base_dispatch(base);

	//释放操作
	evconnlistener_free(listener);
	event_base_free(base);

	return EXIT_SUCCESS;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  read_cb
 *  Description:  读缓冲区回调函数
 * =====================================================================================
 */
void read_cb(struct bufferevent *bev, void *arg)
{
	printf("read_cb收到数据。\n");
	Msg msg;
	User *u_tmp;
	Friend _friend;
	string msgStr;
	string destStr;
	struct evbuffer *input = bufferevent_get_input(bev);
	struct evbuffer *output = bufferevent_get_output(bev);
	int tmp;

	/* 解析数据包 */
	msgStr = unpacket(input);
	if(msgStr == "")
	{
		printf("解析数据包出错。\n");
		return;
	}

	/* json转Msg */
	msg = jsonToMsg(msgStr);

	/* 解析并处理 */
	switch(msg.getType())
	{
		case MsgType::MSG_HEARTBEAT: 		/* 心跳包 */
			/* 封包 + 发送 */
			destStr = packet(msg.toString());
			evbuffer_add(output, destStr.data(), destStr.size());
			break;
		case MsgType::MSG_LOGIN: 			/* 登录 */
			/* 登录校验 */
			u_tmp = us.findUserByUsernameAndPassword(
					msg.getSrc().getUsername(),
					msg.getSrc().getPassword()
					);

			/* 查无此人 */
			if(!u_tmp)
			{
				msg.setType(MsgType::ERRNO_INEXISTENCE);
				destStr = packet(msg.toString());
				evbuffer_add(output, destStr.data(), destStr.size());
				return;
			}

			/* 登录成功 */
			/* 登录 */
			tmp = u_tmp->getId();
			if(onlineMap[tmp] == 0)
				onlineMap[tmp] = bev;
			/* 挤掉 */
			else
			{
				/* 通知被挤掉的人 */
				msg.setType(ERRNO_BEOFFLINE);
				destStr = packet(msg.toString());
				bufferevent_write(onlineMap[tmp], destStr.data(), destStr.size());
				onlineMap[tmp] = bev;
				return;
			}
			/* 修改在线状态 */
			u_tmp->setStatus(UserStatus::USER_STAT_ONLINE);
			us.updateUser(*u_tmp);
			/* 返回用户其他(全部)数据 */
			msg.setType(MsgType::ERRNO_SUCCESS);
			msg.setSrc(*u_tmp);
			destStr = packet(msg.toString());
			evbuffer_add(output, destStr.data(), destStr.size());
			break;
		case MsgType::MSG_REGISTER: 		/* 注册 */
			/* 调用service层，直接返回结果 */
			msg.setType(us.addUser(msg.getSrc()));
			destStr = packet(msg.toString());
			evbuffer_add(output, destStr.data(), destStr.size());
			break;
		case MsgType::MSG_ALTER_PWD: 		/* 修改密码 */
			/* 修改校验 */
			u_tmp = us.findUserByUsernameAndPwdAndMobile(
					msg.getSrc().getUsername(),
					msg.getSrc().getPassword(),
					msg.getSrc().getMobile()
					);

			/* 查无此人 */
			if(!u_tmp)
			{
				msg.setType(MsgType::ERRNO_INEXISTENCE);
				destStr = packet(msg.toString());
				evbuffer_add(output, destStr.data(), destStr.size());
				return;
			}

			/* 修改密码 */
			u_tmp->setPassword(msg.getDest().getPassword());
			us.updateUser(*u_tmp);
			msg.setType(MsgType::ERRNO_SUCCESS);
			destStr = packet(msg.toString());
			evbuffer_add(output, destStr.data(), destStr.size());
			break;
		case MsgType::MSG_FIND_PWD: 		/* 找回密码 */
			/* 用户校验 */
			u_tmp = us.findUserByUsernameAndMobile(
					msg.getSrc().getUsername(),
					msg.getSrc().getMobile()
					);

			/* 查无此人 */
			if(!u_tmp)
			{
				msg.setType(MsgType::ERRNO_INEXISTENCE);
				destStr = packet(msg.toString());
				evbuffer_add(output, destStr.data(), destStr.size());
				return;
			}

			/* 找回密码 */
			u_tmp->setPassword(msg.getDest().getPassword());
			us.updateUser(*u_tmp);
			msg.setType(MsgType::ERRNO_SUCCESS);
			destStr = packet(msg.toString());
			evbuffer_add(output, destStr.data(), destStr.size());
			break;
		case MsgType::COMMAND_FIND_USER: 		/* 查找用户 */
			printf("接收到查找用户请求，开始查找。\n");
			u_tmp = us.findUserByUsername(msg.getSrc().getUsername());

			/* 如果找到了，存入，没有找到，返回id是0的，也就是不需要操作 */
			if(u_tmp)
				msg.setSrc(*u_tmp);

			msg.setType(MsgType::ERRNO_SUCCESS);
			destStr = packet(msg.toString());
			evbuffer_add(output, destStr.data(), destStr.size());
			break;
		case MsgType::COMMAND_ADD_USER: 		/* 加好友 */
			/* 获取对方信息 */
			u_tmp = us.findUserByUsername(msg.getDest().getUsername());

			/* 原来不是好友 */
			if(!fs.findFriend(msg.getSrc(), *u_tmp))
			{
				/* 添加好友 */
				_friend.setSuid(msg.getSrc().getId());
				_friend.setDuid(msg.getDest().getId());
				fs.addFriend(_friend);
			}
			msg.setType(MsgType::ERRNO_SUCCESS);
			destStr = packet(msg.toString());
			evbuffer_add(output, destStr.data(), destStr.size());
			break;
		case MsgType::COMMAND_GET_FRIEND: 		/* 获取好友列表 */
			getFriend(bev, msg);
			break;
		default: break;
	}
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  write_cb
 *  Description:  写缓冲区回调函数
 * =====================================================================================
 */
void write_cb(struct bufferevent *bev, void *arg)
{
	printf("成功写数据给客户端,写缓冲区回调函数被回调.\n");
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  event_cb
 *  Description:  服务器端事件处理回调函数
 * =====================================================================================
 */
void event_cb(struct bufferevent *bev,short events, void *arg)
{
	if (events & BEV_EVENT_EOF)
	{
		printf("连接关闭。\n");
	} 
	else if(events & BEV_EVENT_ERROR)
	{
		printf("连接出现错误！\n");
	}
	else if(events & BEV_EVENT_CONNECTED)
	{
		printf("event_cb,新的连接成功。");
		return;
	}

	bufferevent_free(bev);

	/* 下线处理 */
	auto find_item = find_if(onlineMap.begin(), onlineMap.end(),
			[bev](const map<uint32_t, struct bufferevent *>::value_type item)
			{
			return item.second == bev;
			});
	if (find_item != onlineMap.end())
	{
		/* 数据库状态更新 */
		User *user = us.findUserById(find_item->first);
		user->setStatus(UserStatus::USER_STAT_OFFLINE);
		us.updateUser(*user);

		/* 删除在线列表 */
		onlineMap.erase(find_item);
	}

	printf("bufferevent 资源已经被释放.\n");
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  listener_cb
 *  Description:  服务器端监听事件回调函数
 * =====================================================================================
 */
void listener_cb(struct evconnlistener* listener, evutil_socket_t fd,
		struct sockaddr *addr, int len, void *ptr)
{
	struct event_base *base = (struct event_base*)ptr;
	char buf[256];
	//	int udp_socket;
	//	struct sockaddr_in udp_addr;
	//	struct event udp_event;

	struct sockaddr_in *clie_addr = (struct sockaddr_in *)addr;
	evutil_inet_ntop(clie_addr->sin_family, &clie_addr->sin_addr, buf, sizeof(buf));
	printf("新的连接%d, IP: %s\n", fd, buf);

	//添加新事件
	struct bufferevent* bev;
	bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);

	//给bufferevent缓冲区设置回调
	bufferevent_setcb(bev, read_cb, write_cb, event_cb, NULL);

	//启动bufferevent的读缓冲区，默认是disable的.
	bufferevent_enable(bev, EV_READ);

	/* TODO:加入UDP通信 */
	/*	udp_socket = socket(AF_INET, SOCK_DGRAM, 0);
		memset(&udp_addr, 0, sizeof(udp_addr));
		udp_addr.sin_family = AF_INET;
		udp_addr.sin_port = htons(UDP_SERV_PORT);
		if(bind(udp_socket, (struct sockaddr *)&udp_addr, sizeof(udp_addr)))
		{
		perror("udp bind()");
		exit(1);
		}*/

	/* Add the UDP event */
	/*	event_set(&udp_event, udp_socket, EV_READ | EV_PERSIST, udp_cb, NULL);
		event_add(&udp_event, 0);*/
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  signal_cb
 *  Description:  Ctrl+C信号回调函数
 * =====================================================================================
 */
void signal_cb(evutil_socket_t sig, short events, void *arg)
{
	struct event_base *base = (struct event_base *)arg;
	struct timeval delay = {2, 0};

	/* 退出处理 */

	printf("\n接受到关闭信号，程序将在2秒后退出。。。\n");

	event_base_loopexit(base, &delay);
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  udp_cb
 *  Description:  
 * =====================================================================================
 */
/*
   void udp_cb(const int sock, short int which, void *arg)
   {
   struct sockaddr_in udp_serv_addr;
   socklen_t udp_serv_len = sizeof(udp_serv_addr);
   char buf[BUFSIZ];
   int ret;
   string msgStr;
   Msg msg;

   memset(buf, 0, BUFSIZ);
   ret = recvfrom(sock, &buf, sizeof(buf) - 1, 0, (struct sockaddr *)&udp_serv_addr, &udp_serv_len);
   if(ret == -1)
   {
   perror("recvfrom()");
   event_loopbreak();
   }
   else if(ret == 0)
   {
   printf("udp sock%d close\n", sock);
   return;
   }

   printf("udp clinet: %s\n", buf);
   msgStr = unpacket(buf, ret);
   if(msgStr == "")
   {
   printf("解析数据包出错。\n");
   return;
   }
   msg = jsonToMsg(msgStr);
   switch(msg.getType())
   {

   default: break;
   }*/

/* Send the data back to the client */
/*	if(sendto(sock, buf, sizeof(buf), 0, (struct sockaddr *)&udp_serv_addr, udp_serv_len) == -1)
	{
	perror("sendto()");
	event_loopbreak();
	}
	}*/

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  packet
 *  Description:  封装数据包
 * 					将json数据 压缩/不压缩(默认压缩) 后，插入包头，返回结果
 * =====================================================================================
 */
string packet(const string &msgStr)
{
	char *res;
	char buf[BUFSIZ];
	uint32_t resLen;
	MsgHeader header;
	header.compressflag = MsgHeaderType::COMPRESSED;
	header.originsize = msgStr.size();
	header.compresssize = compressBound(header.originsize);

	/* 压缩，插入消息头 */
	if(header.compressflag == MsgHeaderType::COMPRESSED)
	{
		/* 压缩数据 */
		compress((Bytef*)buf, (uLongf*)&header.compresssize, (Bytef*)msgStr.data(), header.originsize);

		/* 压缩校验 */
		if(header.compresssize <= 0 ||
				header.compresssize > MSGINFO_MAX_LEN)
		{
			printf("压缩结果错误。\n");
			return "";
		}

		resLen = sizeof(header) + header.compresssize;
		res = new char[resLen];
		memcpy(res, &header, sizeof(header));
		memcpy(res + sizeof(header), buf, header.compresssize);
	}
	else
	{
		resLen = sizeof(header) + header.originsize;
		res = new char[resLen];
		memcpy(res, &header, sizeof(header));
		memcpy(res + sizeof(header), msgStr.data(), header.originsize);
	}

	return string(res, resLen);
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  unpacket
 *  Description:  解析数据包
 *  				解析从客户端发来的数据包
 *  				解压并去掉包头，剩Msg的json数据
 * =====================================================================================
 */
string unpacket(evbuffer *input)
{
	char *res;
	MsgHeader header;
	uint32_t len = evbuffer_get_length(input);

	/* 解析数据包 */
	if(len < sizeof(header))
	{
		printf("收到数据，但长度不足，等待下次传输：%d\n", len);
		return "";
	}

	/* 获取数据头 */
	evbuffer_copyout(input, &header, sizeof(header));

	/* 压缩过，需要解压数据包再提取 */
	if(header.compressflag == MsgHeaderType::COMPRESSED)
	{
		/* 包头有错误，立即关闭连接 */
		if(header.originsize <= 0 ||
				header.originsize > MSGINFO_MAX_LEN ||
				header.compresssize <= 0 ||
				header.compresssize > MSGINFO_MAX_LEN)
		{
			printf("包头错误：%d, %d\n", header.originsize, header.compresssize);
			return "";
		}

		/* 收到的数据不够一个完整的数据包 */
		if(len < sizeof(header) + header.compresssize)
			return "";

		/* 获取数据 */
		char *buf = new char[header.compresssize];
		evbuffer_remove(input, &header, sizeof(header));
		evbuffer_remove(input, buf, header.compresssize);

		/* 解压数据 */
		res = new char[header.originsize];
		int ret;
		if((ret = uncompress((Bytef*)res, (uLongf*)&header.originsize, (Bytef*)buf, header.compresssize)) != Z_OK)
		{
			printf("解压失败 %d：%d\n", ret, header.originsize);
			return "";
		}
	}
	/* 没压缩过，直接提取 */
	else
	{
		/* 包头有错误，立即关闭连接 */
		if(header.originsize <= 0 ||
				header.originsize > MSGINFO_MAX_LEN)
		{
			printf("包头错误：%d\n", header.originsize);
			return "";
		}

		/* 收到的数据不够一个完整的数据包 */
		if((uint32_t)len < sizeof(header) + header.originsize)
			return "";

		/* 获取数据 */
		res = new char[header.originsize];
		evbuffer_remove(input, &header, sizeof(header));
		evbuffer_remove(input, res, header.originsize);
	}

	return string(res, header.originsize);
}
string unpacket(char *input, uint32_t size)
{
	char *res;
	MsgHeader header;

	/* 解析数据包 */
	if(size < sizeof(header))
	{
		printf("收到数据，但长度不足，等待下次传输：%d\n", size);
		return "";
	}

	/* 获取数据头 */
	memcpy(&header, input, sizeof(header));

	/* 压缩过，需要解压数据包再提取 */
	if(header.compressflag == MsgHeaderType::COMPRESSED)
	{
		/* 包头有错误，立即关闭连接 */
		if(header.originsize <= 0 ||
				header.originsize > MSGINFO_MAX_LEN ||
				header.compresssize <= 0 ||
				header.compresssize > MSGINFO_MAX_LEN)
		{
			printf("包头错误：%d, %d\n", header.originsize, header.compresssize);
			return "";
		}

		/* 收到的数据不够一个完整的数据包 */
		if(size < sizeof(header) + header.compresssize)
			return "";

		/* 获取数据 */
		char *buf = new char[header.compresssize];
		memcpy(buf, input + sizeof(header), header.compresssize);

		/* 解压数据 */
		res = new char[header.originsize];
		int ret = uncompress((Bytef*)res, (uLongf*)&header.originsize, (Bytef*)buf, header.compresssize);
		if(ret != Z_OK)
		{
			printf("解压失败 %d：%d\n", ret, header.originsize);
			return "";
		}
	}
	/* 没压缩过，直接提取 */
	else
	{
		/* 包头有错误，立即关闭连接 */
		if(header.originsize <= 0 ||
				header.originsize > MSGINFO_MAX_LEN)
		{
			printf("包头错误：%d\n", header.originsize);
			return "";
		}

		/* 收到的数据不够一个完整的数据包 */
		if(size < sizeof(header) + header.originsize)
			return "";

		/* 获取数据 */
		res = new char[header.originsize];
		memcpy(res, input + sizeof(header), header.originsize);
	}

	return string(res, header.originsize);
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  jsonToMsg
 *  Description:  
 * =====================================================================================
 */
Msg jsonToMsg(const string &jsonStr)
{
	Msg msg;
	Group grp;
	User src, dest;
	MsgInfo info;
	list<User> list;

	/* 提取json数据 */
	Json::CharReaderBuilder b;
	Json::CharReader* reader(b.newCharReader());
	Json::Value root;
	JSONCPP_STRING errs;
	bool ok = reader->parse(jsonStr.data(), jsonStr.data() + jsonStr.size(), &root, &errs);
	if (!ok || errs.size() != 0)
	{
		printf("invalid json: %s\n", jsonStr.data());
		delete reader;
		return msg;
	}
	delete reader;

	msg.setType(root["type"].asInt());

	grp.setId(root["group"]["id"].asInt());
	grp.setName(root["group"]["num"].asString());
	grp.setName(root["group"]["name"].asString());
	grp.setDescription(root["group"]["description"].asString());
	grp.setDate(root["group"]["date"].asString());
	msg.setGroup(grp);

	src.setId(root["src"]["id"].asInt());
	src.setUsername(root["src"]["username"].asString());
	src.setPassword(root["src"]["password"].asString());
	src.setPic(root["src"]["pic"].asString());
	src.setNickname(root["src"]["nickname"].asString());
	src.setSign(root["src"]["sign"].asString());
	src.setSex(root["src"]["sex"].asString());
	src.setBirthday(root["src"]["birthday"].asString());
	src.setLocation(root["src"]["location"].asString());
	src.setProfession(root["src"]["profession"].asString());
	src.setMobile(root["src"]["mobile"].asString());
	src.setEmail(root["src"]["email"].asString());
	src.setStatus(root["src"]["status"].asInt());
	src.setDate(root["src"]["date"].asString());
	msg.setSrc(src);

	dest.setId(root["dest"]["id"].asInt());
	dest.setUsername(root["dest"]["username"].asString());
	dest.setPassword(root["dest"]["password"].asString());
	dest.setPic(root["dest"]["pic"].asString());
	dest.setNickname(root["dest"]["nickname"].asString());
	dest.setSign(root["dest"]["sign"].asString());
	dest.setSex(root["dest"]["sex"].asString());
	dest.setBirthday(root["dest"]["birthday"].asString());
	dest.setLocation(root["dest"]["location"].asString());
	dest.setProfession(root["dest"]["profession"].asString());
	dest.setMobile(root["dest"]["mobile"].asString());
	dest.setEmail(root["dest"]["email"].asString());
	dest.setStatus(root["dest"]["status"].asInt());
	dest.setDate(root["dest"]["date"].asString());
	msg.setDest(dest);

	info.setInfo(root["info"]["info"].asString());
	Json::Value userListInfoRoot = root["info"]["userListInfo"];
	int userListInfoSize = userListInfoRoot.size();
	for(int i = 0; i < userListInfoSize; i++)
	{
		Json::Value userRoot = userListInfoRoot[i]["root"];
		User user;
		user.setId(userRoot["id"].asInt());
		user.setUsername(userRoot["username"].asString());
		user.setPassword(userRoot["password"].asString());
		user.setPic(userRoot["pic"].asString());
		user.setNickname(userRoot["nickname"].asString());
		user.setSign(userRoot["sign"].asString());
		user.setSex(userRoot["sex"].asString());
		user.setBirthday(userRoot["birthday"].asString());
		user.setLocation(userRoot["location"].asString());
		user.setProfession(userRoot["profession"].asString());
		user.setMobile(userRoot["mobile"].asString());
		user.setEmail(userRoot["email"].asString());
		user.setStatus(userRoot["status"].asInt());
		user.setDate(userRoot["date"].asString());
		list.push_back(user);
	}
	info.setUserListInfo(list);
	msg.setInfo(info);

	return msg;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  getFriend
 *  Description:  
 * =====================================================================================
 */
void getFriend(struct bufferevent *bev, Msg &msg)
{
	MsgInfo info;
	string destStr;

	list<User> list = fs.findUserAllByUser(msg.getSrc());

	info.setUserListInfo(list);
	msg.setInfo(info);
	destStr = packet(msg.toString());
	bufferevent_write(bev, destStr.data(), destStr.size());
}

