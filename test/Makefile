obj=$(wildcard *.o)
user_obj=UserTest.o User.o
group_obj=GroupTest.o Group.o
friend_obj=FriendTest.o Friend.o
usergroupmap_obj=UsergroupmapTest.o Usergroupmap.o
ConnectionPool_obj=ConnectionPoolTest.o ConnectionPool.o ConfigFileReader.o User.o
target=UserTest GroupTest FriendTest UsergroupmapTest ConnectionPoolTest
CFLAGS=-Wall -std=c++11 -lpthread -L/usr/lib64/mysql/ -lmysqlclient
CC=g++

all:$(target)

UserTest:$(user_obj)
	$(CC) $^ -o $@ $(CFLAGS)

GroupTest:$(group_obj)
	$(CC) $^ -o $@ $(CFLAGS)

FriendTest:$(friend_obj)
	$(CC) $^ -o $@ $(CFLAGS)

UsergroupmapTest:$(usergroupmap_obj)
	$(CC) $^ -o $@ $(CFLAGS)

ConnectionPoolTest:$(ConnectionPool_obj)
	$(CC) $^ -o $@ $(CFLAGS)

UserTest.o:UserTest.cpp ../pojo/User.cpp ../pojo/User.h
	$(CC) -c $< -o $@ $(CFLAGS)

User.o:../pojo/User.cpp ../pojo/User.h
	$(CC) -c $< -o $@ $(CFLAGS)

GroupTest.o:GroupTest.cpp ../pojo/Group.cpp ../pojo/Group.h
	$(CC) -c $< -o $@ $(CFLAGS)

Group.o:../pojo/Group.cpp ../pojo/Group.h
	$(CC) -c $< -o $@ $(CFLAGS)

FriendTest.o:FriendTest.cpp ../pojo/Friend.cpp ../pojo/Friend.h
	$(CC) -c $< -o $@ $(CFLAGS)

Friend.o:../pojo/Friend.cpp ../pojo/Friend.h
	$(CC) -c $< -o $@ $(CFLAGS)

UsergroupmapTest.o:UsergroupmapTest.cpp ../pojo/Usergroupmap.cpp ../pojo/Usergroupmap.h
	$(CC) -c $< -o $@ $(CFLAGS)

Usergroupmap.o:../pojo/Usergroupmap.cpp ../pojo/Usergroupmap.h
	$(CC) -c $< -o $@ $(CFLAGS)

ConnectionPoolTest.o:ConnectionPoolTest.cpp ../include/ConnectionPool.cpp \
	../include/ConnectionPool.h ../pojo/User.cpp ../pojo/User.h

	$(CC) -c $< -o $@ $(CFLAGS)

ConnectionPool.o:../include/ConnectionPool.cpp ../include/ConnectionPool.h \
	../include/ConfigFileReader.cpp ../include/ConfigFileReader.h
	$(CC) -c $< -o $@ $(CFLAGS)

ConfigFileReader.o:../include/ConfigFileReader.cpp ../include/ConfigFileReader.h
	$(CC) -c $< -o $@ $(CFLAGS)

.PHONY:clean
clean:
	rm -rf $(target) $(obj)

