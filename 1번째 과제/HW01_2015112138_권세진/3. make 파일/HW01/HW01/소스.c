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
	int i = 0;// �Էµ� �л����� �����մϴ�.


	while (!feof(file) && i < MAX) { // ������ ���� �ٴٶ��ų� �迭�� ������ ���������� �о���̱⸦ �����մϴ�.
		fscanf_s(file, "%lu %s", &(myClass[i].sid), &(myClass[i].name), sizeof(myClass[i].name));
		printf("(%lu %s)", myClass[i].sid, myClass[i].name);
		i++;
	}
	printf("\n.....%i���� �̸��� �ԷµǾ��ֽ��ϴ�.\n", i);
	char buffer[20];
	char ch = 'y';
	printf("�й� -> �̸� / �̸� -> �й� ���α׷� by 2015112138 �Ǽ���-----------------------\n");
	while (ch == 'y') {
		printf("�й��̳� �̸��� �Է����ּ���\n");
		scanf_s("%s", buffer, sizeof(buffer)); getchar();
		if (buffer[0] >= '0' && buffer[0] <= '9') {
			//�й��� �Է��ϸ� 
			for (int k = 0; k < MAX; k++) {
				if (myClass[k].sid == atol(buffer)) {
					//�Է��� �й��� ���� ����� �й��� ã�� �� �迭�� ����� �̸��� ������ݴϴ�.
					printf("�Է��� �й��� %s�� �й��Դϴ�\n", myClass[k].name);
					break;
				}
				if (k == MAX - 1) {
					//myClass�� �迭�� ��� Ȯ���ߴµ� ã�����ߴٸ� �Ʒ������� ����մϴ�.
					printf("%s�� ����� ����ü �迭�� ���� �й��Դϴ�. \n", buffer);
				}
			}
		}
		else {
			//�̸��� �Է��ϸ�
			for (int k = 0; k < MAX; k++) {
				if (!strcmp(myClass[k].name, buffer)) {
					//�Է��� �̸��� ���� ����� �̸��� ã�� �� �迭�� ����� �й��� ������ݴϴ�.
					printf("�Է��� �̸��� �й��� %lu�Դϴ�. \n", myClass[k].sid);
					break;
				}
				if (k == MAX - 1) {
					//myClass�� �迭�� ��� Ȯ���ߴµ� ã�����ߴٸ� �Ʒ������� ����մϴ�.
					printf("%s�� ����� ����ü �迭�� ���� �̸��Դϴ�. \n", buffer);
				}
			}
		}
		printf("����Ͻðڽ��ϱ�? (y/n)");
		ch = getchar(); // y�� �ԷµǸ� while ������ �ٽ� �����ϰ� �ƴϸ� ���α׷��� ��Ĩ�ϴ�.
	}
	system("pause");
}