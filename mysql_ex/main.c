//#include <my_global.h>
#include <stdio.h>
#include <mysql/mysql.h>// libmysql:x64-windows
#include "db_config.h"// ���� ������ ����ִ� ȯ�漳�� ����

#define CHOP(x) x[strlen(x) - 1] = ' '

#define TRUE 1
#define FALSE 0

int main(void)
{
    MYSQL mysql;
    mysql_init(&mysql);
    //mysql ���� �õ�, connection : �������� �� �� ����. ���н� NULL ��ȯ
    MYSQL* connection = mysql_real_connect(&mysql, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, NULL, 0);
    
    if (connection == NULL)
        printf("DB ���� ����\n");
    else
        printf("DB ���� ����\n");

    int query_result;
    char insert_q[50] = "INSERT INTO korea VALUES('TOKO', 10000)";
    
    // Query ����
    query_result = mysql_query(connection, insert_q);
   
    // �����ϸ� 0, �����ϸ� �ٸ� ���� ��ȯ (ex 100)
    if (query_result == 0)
        printf("%s ����\n", insert_q);
    else
        printf("%s ����\n", insert_q);

    
    mysql_close(&mysql);
}

