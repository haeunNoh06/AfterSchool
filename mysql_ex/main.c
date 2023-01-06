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
        printf("DB 연결 실패");
    else
        printf("DB 연결 성공");


    
    
    mysql_close(&mysql);
}

