#include <stdio.h>
#include <string.h>//���ڿ� ���̺귯��
#include <stdlib.h>//itoa���

int main(void) {
	
	char str[30] = "score : ";
	int score = 300;

	sprintf(str, "score : %d", score);//sprintf : string�� ����, ���ڿ����� ������� == str�� ����� �ִ� ���ڿ��� ��

	printf("%s\n", str);

	return 0;
}