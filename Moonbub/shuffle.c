#include <stdio.h>
#include <stdlib.h>// srand(), rand()
#include <time.h>// time()

void swap(int* a, int* b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

// arr�� ���빰�� �������� ���´�
void shuffle(int* arr[][4])
{
	srand(time(0));
	for (int i = 0; i < 25; i++) {
		for (int j = 0; j < 25; j++) {
			// 0~15���� ���;� �ϹǷ� 16�� �������� ���ϴ� ������ ���
			swap(&arr[rand()%4][rand() % 4], &arr[rand() % 4][rand()%4]);
		}
	}
}

int main(void) {

	const int S = 4;
	//int arr[16] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 };
	int arr[4][4] = { 100,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 };

	shuffle(arr);

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			printf("%d ", arr[i][j]);
		}
	}

	return 0;
}