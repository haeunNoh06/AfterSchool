//#include <my_global.h>
#include <stdio.h>
#include <mysql/mysql.h>// libmysql:x64-windows
#include "db_config.h"// 개인 정보가 들어있는 환경설정 파일

#define CHOP(x) x[strlen(x) - 1] = ' '

#define TRUE 1
#define FALSE 0

int main(void)
{
    MYSQL mysql;
    mysql_init(&mysql);
    //mysql 연결 시도, connection : 연결결과를 볼 수 있음. 실패시 NULL 반환
    MYSQL* connection = mysql_real_connect(&mysql, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, NULL, 0);
    
    if (connection == NULL)
        printf("DB 연결 실패\n");
    else
        printf("DB 연결 성공\n");

    int query_result;
    char insert_q[50] = "INSERT INTO korea VALUES('TOKO', 10000)";
    
    // Query 실행
    query_result = mysql_query(connection, insert_q);
   
    // 성공하면 0, 실패하면 다른 값을 반환 (ex 100)
    if (query_result == 0)
        printf("%s 성공\n", insert_q);
    else
        printf("%s 실패\n", insert_q);

    
    mysql_close(&mysql);
}

