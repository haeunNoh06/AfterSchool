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
    //char insert_q[50] = "INSERT INTO korea VALUES('TOKO', 10000)";
    //

    //// Query 실행
    //query_result = mysql_query(connection, insert_q);
   
    //// 성공하면 0, 실패하면 다른 값을 반환 (ex 100)
    //if (query_result == 0)
    //    printf("%s 성공\n", insert_q);
    //else

    // UPDATE
    //char update_q[100] = "UPDATE korea SET population = 100000 WHERE city = 'TOKO'";
    //
    //// Query 실행
    //query_result = mysql_query(connection, update_q);
   
    //// 성공하면 0, 실패하면 다른 값을 반환 (ex 100)
    //if (query_result == 0)
    //    printf("%s 성공\n", update_q);
    //else
    //    printf("%s 실패\n", update_q) // UPDATE

    // DELETE
    //char delete_q[100] = "DELETE FROM korea WHERE city = 'TOKO'";
    //
    //// Query 실행
    //query_result = mysql_query(connection, delete_q);
   
    //// 성공하면 0, 실패하면 다른 값을 반환 (ex 100)
    //if (query_result == 0)
    //    printf("%s 성공\n", delete_q);
    //else
    //    printf("%s 실패\n", delete_q);

    // SELECT : 데이터를 가져와야 함. INSERT, UPDATE, DELETE는 MySQL 쿼리만 하면 되는데 SELECT는 처리해야 할 것이 많음
    char select_q[100] = "SELECT * FROM korea";

    // Query 실행
    // DB 실제 데이터는 connection에 있음
    query_result = mysql_query(connection, select_q);
    if (query_result == 0)
        printf("%s 성공\n", select_q);
    else
        printf("%s 실패\n", select_q);

    MYSQL_RES* select_result;
    select_result = mysql_store_result(connection);
    MYSQL_ROW sql_row;
    
    // sql_row의 값이 없을 때까지 각각의 행(row)들을 접근하겠다. java의 .next()와 비슷함
    while (TRUE)
    {
        sql_row = mysql_fetch_row(select_result);// 각 행(data)을 sql_row가 받음
        if (sql_row == NULL)// 더 이상 받을 행이 없으면
            break;// 반복문 빠져나감

        // DB는 int형 데이터도 문자열로 받는다(sql_row[1])
        printf("%s %s\n", sql_row[0], sql_row[1]);
        
    }


    mysql_close(&mysql);// mysql 종료
}

