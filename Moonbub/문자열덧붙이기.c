#include <stdio.h>
#include <string.h>//문자열 라이브러리
#include <stdlib.h>//itoa사용

int main(void) {
	
	char str[30] = "score : ";
	int score = 300;

	sprintf(str, "score : %d", score);//sprintf : string의 약자, 문자열에다 출력해줌 == str에 가운데에 있는 문자열이 들어감

	printf("%s\n", str);

	return 0;
}