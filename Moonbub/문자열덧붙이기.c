#include <stdio.h>

int main(void) {
	
	char str[30] = "score : ";
	char str2[30] = "300";

	strcat(str, str2);
	

	printf("%s\n", str);

	return 0;
}