obj=$(wildcard *.o)
ConnectionPool_lib=ConnectionPool.o ConfigFileReader.o Specification.o
UserService_obj=UserServiceTest.o User.o UserDao.o UserService.o $(ConnectionPool_lib)
GroupService_obj=GroupServiceTest.o Group.o GroupDao.o GroupService.o $(ConnectionPool_lib)\
				 User.o UserDao.o UserService.o
FriendService_obj=FriendServiceTest.o Friend.o FriendDao.o FriendService.o $(ConnectionPool_lib) \
				  User.o UserDao.o UserService.o
UserGroupMapService_obj=UserGroupMapServiceTest.o UserGroupMap.o UserGroupMapDao.o \
						UserGroupMapService.o $(ConnectionPool_lib) \
						User.o UserDao.o UserService.o
target=UserServiceTest GroupServiceTest FriendServiceTest UserGroupMapServiceTest
CFLAGS=-Wall -std=c++11 -lpthread -L/usr/lib64/mysql/ -lmysqlclient
CC=g++

all:$(target)

UserServiceTest:$(UserService_obj)
	$(CC) $^ -o $@ $(CFLAGS)

GroupServiceTest:$(GroupService_obj)
	$(CC) $^ -o $@ $(CFLAGS)

FriendServiceTest:$(FriendService_obj)
	$(CC) $^ -o $@ $(CFLAGS)

UserGroupMapServiceTest:$(UserGroupMapService_obj)
	$(CC) $^ -o $@ $(CFLAGS)

ConnectionPoolTest:$(ConnectionPool_obj)
	$(CC) $^ -o $@ $(CFLAGS)

UserServiceTest.o:UserServiceTest.cpp ../pojo/User.cpp ../pojo/User.h \
	../dao/UserDao.cpp ../dao/UserDao.h \
	../service/UserService.cpp ../service/UserService.h
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

GroupServiceTest.o:GroupServiceTest.cpp ../pojo/Group.cpp ../pojo/Group.h \
	../dao/GroupDao.cpp ../dao/GroupDao.h \
	../service/GroupService.cpp ../service/GroupService.h
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

FriendServiceTest.o:FriendServiceTest.cpp ../pojo/Friend.cpp ../pojo/Friend.h \
	../dao/FriendDao.cpp ../dao/FriendDao.h \
	../service/FriendService.cpp ../service/FriendService.h
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

UserGroupMapServiceTest.o:UserGroupMapServiceTest.cpp ../pojo/UserGroupMap.cpp ../pojo/UserGroupMap.h \
	../dao/UserGroupMapDao.cpp ../dao/UserGroupMapDao.h \
	../service/UserGroupMapService.cpp ../service/UserGroupMapService.h
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

.PHONY:clean
clean:
	rm -rf $(target) $(obj)

