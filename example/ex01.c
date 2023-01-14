#include <stdio.h>

int main(void)
{
	int num1[3][3];
	int num2[3][3];
	int sum;

	// 입력
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			printf("숫자 입력 : ");
			scanf_s("%d", &num1[i][j]);
		}
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			printf("숫자 입력 : ");
			scanf_s("%d", &num2[i][j]);
		}
	}

	// 처리
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			sum = num1[i][j] + num2[i][j];
			printf("%d\n", sum);
		}
	}

	return 0;
}