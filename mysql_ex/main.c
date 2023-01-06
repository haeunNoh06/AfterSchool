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
    //char insert_q[50] = "INSERT INTO korea VALUES('TOKO', 10000)";
    //

    //// Query ����
    //query_result = mysql_query(connection, insert_q);
   
    //// �����ϸ� 0, �����ϸ� �ٸ� ���� ��ȯ (ex 100)
    //if (query_result == 0)
    //    printf("%s ����\n", insert_q);
    //else

    // UPDATE
    //char update_q[100] = "UPDATE korea SET population = 100000 WHERE city = 'TOKO'";
    //
    //// Query ����
    //query_result = mysql_query(connection, update_q);
   
    //// �����ϸ� 0, �����ϸ� �ٸ� ���� ��ȯ (ex 100)
    //if (query_result == 0)
    //    printf("%s ����\n", update_q);
    //else
    //    printf("%s ����\n", update_q) // UPDATE

    char delete_q[100] = "DELETE FROM korea WHERE city = 'TOKO'";
    
    // Query ����
    query_result = mysql_query(connection, delete_q);
   
    // �����ϸ� 0, �����ϸ� �ٸ� ���� ��ȯ (ex 100)
    if (query_result == 0)
        printf("%s ����\n", delete_q);
    else
        printf("%s ����\n", delete_q);

    mysql_close(&mysql);
}

