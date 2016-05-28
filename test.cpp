#include <windows.h>
#include "stdio.h"
#include "winsock.h" 
#include "mysql.h" 
#pragma warning (disable:4996)

int main()
{

	MYSQL * con; //= mysql_init((MYSQL*) 0); 
	MYSQL_RES *res;
	MYSQL_ROW row;


	char tmp[400];

	//database configuartion
	char dbuser[30] = "root";
	char dbpasswd[30] = "8023love521";
	char dbip[30] = "localhost";
	char dbname[50] = "mydata";
	char tablename[50] = "xqdata";
	char *query = NULL;


	int x;
	int y;
	int rt;//return value
	unsigned int t;

	int count = 0;


	printf("input x,y\n");
	scanf("%d,%d", &x, &y);
	fflush(stdin);
	printf("input over\n");
	con = mysql_init((MYSQL*)0);


	if (con != NULL && mysql_real_connect(con, dbip, dbuser, dbpasswd, dbname, 3306/*TCP IP端口*/, NULL/*Unix Socket 连接类型*/, 0/*运行成ODBC数据库标志*/))
	{
		if (!mysql_select_db(con, dbname))
		{
			printf("Select successfully the database!\n");

			con->reconnect = 1;

			query = "set names \'GBK\'";
			//mysql_query(con,"set names \'GBK\'"); 

			rt = mysql_real_query(con, query, strlen(query));
			if (rt)
			{
				printf("Error making query: %s !!!\n", mysql_error(con));
			}
			else
			{
				printf("query %s succeed!\n", query);
			}

		}
	}

	else
	{
		MessageBoxA(NULL, "Unable to connect the database,check your configuration!", "", NULL);

	}

	//sprintf(tmp,"update %s set 商品=\'%s\',卖出=%d,成交=%d,涨跌=%d,买进=%d,总量=%d,涨幅=%f,时间=\'%s\' where  %s",tablename,goods,sold,deal,fluctuate,buy,total,delta,time,UpdateCon);
	sprintf(tmp, "insert into %s values(%s,%d,%d)", tablename, "null", x, y); //注意如何向具有自增字段的数据库中插入记录
																			  //MessageBoxA(NULL,tmp,tmp,MB_OK);
																			  //mysql_query(con,tmp);

	rt = mysql_real_query(con, tmp, strlen(tmp));
	if (rt)
	{
		printf("Error making query: %s !!!\n", mysql_error(con));
	}
	else
	{
		printf("%s executed!!!\n", tmp);
	}

	sprintf(tmp, "select * from %s", tablename);

	rt = mysql_real_query(con, tmp, strlen(tmp));
	if (rt)
	{
		printf("Error making query: %s !!!\n", mysql_error(con));
	}
	else
	{
		printf("%s executed!!!\n", tmp);
	}

	res = mysql_store_result(con);//将结果保存在res结构体中

	while (row = mysql_fetch_row(res))
	{
		/**
		* MYSQL_ROW STDCALL mysql_fetch_row(MYSQL_RES *result);
		* 检索行
		*/

		for (t = 0; t<mysql_num_fields(res); t++)
		{
			printf("%s  ", row[t]);
		}
		printf(".............\n");
		count++;
	}
	printf("number of rows %d\n", count);
	printf("mysql_free_result...\n");
	mysql_free_result(res);

	mysql_close(con);
	return 0;

}
