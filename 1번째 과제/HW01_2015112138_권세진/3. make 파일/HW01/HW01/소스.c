#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 2015112138%10+5
typedef struct Student
{
	char name[20];
	unsigned long sid;
}Student;

void main() {
	Student myClass[MAX];

	FILE *file = NULL;
	errno_t err;
	err = fopen_s(&file, "student.txt", "r");
	int i = 0;// 입력된 학생수를 저장합니다.


	while (!feof(file) && i < MAX) { // 파일의 끝에 다다랐거나 배열의 끝까지 저장했을때 읽어들이기를 종료합니다.
		fscanf_s(file, "%lu %s", &(myClass[i].sid), &(myClass[i].name), sizeof(myClass[i].name));
		printf("(%lu %s)", myClass[i].sid, myClass[i].name);
		i++;
	}
	printf("\n.....%i명의 이름이 입력되어있습니다.\n", i);
	char buffer[20];
	char ch = 'y';
	printf("학번 -> 이름 / 이름 -> 학번 프로그램 by 2015112138 권세진-----------------------\n");
	while (ch == 'y') {
		printf("학번이나 이름을 입력해주세요\n");
		scanf_s("%s", buffer, sizeof(buffer)); getchar();
		if (buffer[0] >= '0' && buffer[0] <= '9') {
			//학번을 입력하면 
			for (int k = 0; k < MAX; k++) {
				if (myClass[k].sid == atol(buffer)) {
					//입력한 학번과 같은 저장된 학번을 찾고 그 배열에 저장된 이름을 출력해줍니다.
					printf("입력한 학번은 %s의 학번입니다\n", myClass[k].name);
					break;
				}
				if (k == MAX - 1) {
					//myClass의 배열을 모두 확인했는데 찾지못했다면 아래내용을 출력합니다.
					printf("%s는 저장된 구조체 배열에 없는 학번입니다. \n", buffer);
				}
			}
		}
		else {
			//이름을 입력하면
			for (int k = 0; k < MAX; k++) {
				if (!strcmp(myClass[k].name, buffer)) {
					//입력한 이름과 같은 저장된 이름을 찾고 그 배열에 저장된 학번을 출력해줍니다.
					printf("입력한 이름의 학번은 %lu입니다. \n", myClass[k].sid);
					break;
				}
				if (k == MAX - 1) {
					//myClass의 배열을 모두 확인했는데 찾지못했다면 아래내용을 출력합니다.
					printf("%s는 저장된 구조체 배열에 없는 이름입니다. \n", buffer);
				}
			}
		}
		printf("계속하시겠습니까? (y/n)");
		ch = getchar(); // y가 입력되면 while 루프를 다시 진행하고 아니면 프로그램을 마칩니다.
	}
	system("pause");
}