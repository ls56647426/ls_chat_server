/*
 * =====================================================================================
 *
 *       Filename:  ConnectionPoolTest.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/21/2020 03:44:47 PM
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

#include "../include/ConnectionPool.h"
#include "../pojo/User.h"

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
int main ( int argc, char *argv[] )
{
	User *user = new User();
	MYSQL_RES *result = ConnectionPool::runOne("select * from user;");

	int field_num = mysql_num_fields(result);
	MYSQL_FIELD *fields = mysql_fetch_fields(result);
	
	printf("------------------------------------------\n");
	for(int i= 0; i < field_num; i++)
	{
		cout << fields[i].name << "\t";
	}
	printf("\n------------------------------------------\n");

	//表内容
	MYSQL_ROW row = NULL;
	while(row = mysql_fetch_row(result))
	{
		for(int i = 0; i < field_num; i++)
			cout << row[i] << "\t";
		
		cout << endl;
	}

	return EXIT_SUCCESS;
}

