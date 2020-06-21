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

#include "../pojo/Friend.h"

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
int main ( int argc, char *argv[] )
{
	Friend *_friend = new Friend();

	_friend->setUid1(1);
	_friend->setUid2(2);

	cout << _friend->toString() << endl;

	return EXIT_SUCCESS;
}

