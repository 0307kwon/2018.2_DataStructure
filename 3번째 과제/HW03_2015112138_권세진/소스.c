#include "���.h"
#include <stdio.h>


void main() {
	int bullet;


	Head* gameHead = CreateHead();

	Head* myhead = CreateHead();

	srand(time(NULL));

	FILE* file = NULL;
	errno_t err = fopen_s(&file,"student.txt", "r");
	char str[20];
	char* strTemp;
	while (!feof(file)) {

		fscanf_s(file, "%s \n", str, 20);
		strTemp = (char*)malloc(sizeof(char) * 20);
		strcpy_s(strTemp, 20, str, 20);
		InsertNode(myhead, 0, strTemp,0);
	}

	printf("--------- ���þȷ귿 ���� --------- by 2015112138 �Ǽ��� \n");
	printf("����Ű�� ������ �����մϴ�.\n");
	getchar();

	
	


	char deadName[20];
	int count = myhead->count;
	for (int i = 0; i < count; i++) {
		bullet = Random(10);
		
		DeleteMan(myhead, bullet,deadName);
		InsertNode(gameHead, 0, deadName,bullet);
		
	}
	PrintALL(gameHead);
	
	getchar();
	
}