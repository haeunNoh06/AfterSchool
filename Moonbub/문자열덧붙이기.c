#include <stdio.h>

int main(void) {
	
	char str[30] = "score : ";
	//str�� ���� �� ���ϱ�
	int str_len = strlen(str);

	char str2[30] = "300";
	//str2�� ���� �� ���ϱ�
	int str2_len = strlen(str2);
	
	for (int i = 0; i < str2_len; i++)
		str[i + str_len] = str2[i];

	printf("%s\n", str);

	return 0;
}