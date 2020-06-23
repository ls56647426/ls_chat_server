CC=g++
LIBS=-L/usr/lib64/mysql/ -lmysqlclient
LIBS+=-L/usr/local/lib/ -levent
LIBS+=-lpthread
CFLAGS=-Wall -std=c++11

ConnectionPool_obj=ConnectionPool.o ConfigFileReader.o Specification.o
UserService_obj=UserService.o UserDao.o User.o
GroupService_obj=GroupService.o GroupDao.o Group.o
FriendService_obj=FriendService.o FriendDao.o Friend.o
UserGroupMapService_obj=UserGroupMapService.o UserGroupMapDao.o UserGroupMap.o
object=server.o $(ConnectionPool_obj) $(UserService_obj) $(GroupService_obj) \
	   $(FriendService_obj) $(UserGroupMapService_obj) Msg.o
target=server

$(target):$(object)
	$(CC) $^ -o $@ $(CFLAGS) $(LIBS)

server.o:../server.cpp ../server.h
	$(CC) -c $< -o $@ $(CFLAGS)

User.o:../pojo/User.cpp ../pojo/User.h
	$(CC) -c $< -o $@ $(CFLAGS)

UserDao.o:../dao/UserDao.cpp ../dao/UserDao.h \
	../pojo/User.cpp ../pojo/User.h
	$(CC) -c $< -o $@ $(CFLAGS)

UserService.o:../service/UserService.cpp ../service/UserService.h \
	../dao/UserDao.cpp ../dao/UserDao.h \
	../pojo/User.cpp ../pojo/User.h
	$(CC) -c $< -o $@ $(CFLAGS)

Group.o:../pojo/Group.cpp ../pojo/Group.h
	$(CC) -c $< -o $@ $(CFLAGS)

GroupDao.o:../dao/GroupDao.cpp ../dao/GroupDao.h \
	../pojo/Group.cpp ../pojo/Group.h
	$(CC) -c $< -o $@ $(CFLAGS)

GroupService.o:../service/GroupService.cpp ../service/GroupService.h \
	../dao/GroupDao.cpp ../dao/GroupDao.h \
	../pojo/Group.cpp ../pojo/Group.h
	$(CC) -c $< -o $@ $(CFLAGS)

Friend.o:../pojo/Friend.cpp ../pojo/Friend.h
	$(CC) -c $< -o $@ $(CFLAGS)

FriendDao.o:../dao/FriendDao.cpp ../dao/FriendDao.h \
	../pojo/Friend.cpp ../pojo/Friend.h
	$(CC) -c $< -o $@ $(CFLAGS)

FriendService.o:../service/FriendService.cpp ../service/FriendService.h \
	../dao/FriendDao.cpp ../dao/FriendDao.h \
	../pojo/Friend.cpp ../pojo/Friend.h
	$(CC) -c $< -o $@ $(CFLAGS)

UserGroupMap.o:../pojo/UserGroupMap.cpp ../pojo/UserGroupMap.h
	$(CC) -c $< -o $@ $(CFLAGS)

UserGroupMapDao.o:../dao/UserGroupMapDao.cpp ../dao/UserGroupMapDao.h \
	../pojo/UserGroupMap.cpp ../pojo/UserGroupMap.h
	$(CC) -c $< -o $@ $(CFLAGS)

UserGroupMapService.o:../service/UserGroupMapService.cpp ../service/UserGroupMapService.h \
	../pojo/UserGroupMap.cpp ../pojo/UserGroupMap.h \
	../dao/UserGroupMapDao.cpp ../dao/UserGroupMapDao.h
	$(CC) -c $< -o $@ $(CFLAGS)

ConnectionPool.o:../include/ConnectionPool.cpp ../include/ConnectionPool.h \
	../include/ConfigFileReader.cpp ../include/ConfigFileReader.h \
	../include/Specification.cpp ../include/Specification.h
	$(CC) -c $< -o $@ $(CFLAGS)

ConfigFileReader.o:../include/ConfigFileReader.cpp ../include/ConfigFileReader.h
	$(CC) -c $< -o $@ $(CFLAGS)

Specification.o:../include/Specification.cpp ../include/Specification.h
	$(CC) -c $< -o $@ $(CFLAGS)

Msg.o:../include/Msg.cpp ../include/Msg.h
	$(CC) -c $< -o $@ $(CFLAGS)

.PHONY:clean
clean:
	rm -rf $(target) $(object)

