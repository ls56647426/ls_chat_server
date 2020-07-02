/*
 * =====================================================================================
 *
 *       Filename:  MessageServiceTest.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/02/2020 09:57:15 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stdlib.h>

#include "../service/MessageService.h"

#include <iostream>

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
int main ( int argc, char *argv[] )
{
	User user;
	MessageService ms;
	list<Message> list;

	user.setId(1);
	list = ms.findMessageByUser(user);

	for(auto it = list.begin(); it != list.end(); it++)
		cout << it->toString() << endl;

	return EXIT_SUCCESS;
}

