/*
 * =====================================================================================
 *
 *       Filename:  friendtest.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/19/2020 09:07:58 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stdlib.h>

#include <iostream>
using namespace std;

#include "../service/UserService.h"
#include "../service/FriendService.h"

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
int main ( int argc, char *argv[] )
{
	UserService us;
	FriendService fs;
	User *user = us.findUserById(1);
	list<Friend> list = fs.findAllByUser(*user);

	for(auto _friend : list)
		cout << _friend.toString() << endl;

	return EXIT_SUCCESS;
}

