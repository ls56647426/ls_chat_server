/*
 * =====================================================================================
 *
 *       Filename:  usergrouptest.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/19/2020 09:33:41 PM
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
#include "../service/UserGroupMapService.h"

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
int main ( int argc, char *argv[] )
{
	UserService us;
	UserGroupMapService ugms;
	User *user = us.findUserById(1);
	list<UserGroupMap> list = ugms.findAllByUser(*user);

	for(auto ugm : list)
		cout << ugm.toString() << endl;

	return EXIT_SUCCESS;
}

