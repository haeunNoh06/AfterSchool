#include <stdio.h>
#include <stdlib.h>// srand(), rand()
#include <time.h>// time()

void swap(int* a, int* b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

// arr의 내용물을 무작위로 섞는다
void shuffle(int* arr[][4])
{
	srand(time(0));
	for (int i = 0; i < 25; i++) {
		for (int j = 0; j < 25; j++) {
			// 0~15까지 나와야 하므로 16의 나머지를 구하는 연산을 사용
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