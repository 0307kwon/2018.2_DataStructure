#include <stdio.h>
#include<malloc.h>
#include<string.h>
#include "header.h"



NODE* CreateNode(char* name[20], unsigned long sid) {
	NODE* nodePtr = (NODE*)malloc(sizeof(NODE));
	if (nodePtr == NULL) {
		printf("힙에 공간이 부족합니다");
	}
	strcpy_s(nodePtr->name, 20, name, 20);
	nodePtr->sid = sid;
	nodePtr->link = NULL;
	printf("%s %d \n", name, sid);
	return nodePtr;
}

void Clear(NODE* head) { // Linked list에 할당된 힙을 모두 free합니다.
	NODE* temp = head;
	NODE* temp2 = NULL;
	int i = 1;
	while (1) {
		temp2 = temp->link; // 노드를 free하기전에 다음 link의 주소를 임시저장합니다.
		free(temp);

		if (temp2 != NULL) {
			temp = temp2;
			i++;
		}
		else {
			break;
		}
	}
	printf("Linked list free 완료\n", i);
}



NODE* FindNode_S(char* s[20]) { // 인자와 같은 값을 가진 노드를 찾습니다. (인자가 글자일때)
	NODE* node = head;
	while (node != NULL) {
		if (!strcmp(node->name, s)) { // 같은 값을 찾으면
			return node;
		}
		else {
			node = node->link;
		}
	}	
	return NULL; // 링크가 끝날때까지 못찾으면 NULL을 리턴

}

NODE* FindNode_N(unsigned long sid) {
	NODE* node = head;
	while (node != NULL) {
		if (node->sid == sid) {
			return node;
		}
		else {
			node = node->link;
		}
	}
	return NULL; // 링크가 끝날때까지 못찾으면 NULL을 리턴
}

void ChangeTo() { // input.txt를 읽어서 학번 ->이름 , 이름 -> 학번 으로 변경해줍니다.
	FILE* file = NULL;
	errno_t err = fopen_s(&file, "input.txt", "rt");
	NODE* temp = NULL;
	char* string[20];
	while (!feof(file)) {
		fscanf_s(file, "%s", string, 20);
		if (IsString(string)) { // 이름이면 학번으로 바꿔주세용
			temp = FindNode_S(string);
			if (temp != NULL) {
				printf("%d\n", temp->sid);
			}
			else {
				printf("없는 이름입니다.\n");
			}
		}
		else {//학번이면 이름으로 바꿔주세용
			temp = FindNode_N(atol(string));
			if (temp != NULL) {
				printf("%s\n", temp->name);
			}
			else {
				printf("없는 학번입니다.\n");
			}
		}
	}
}


int IsString(char* s[20]) { // 글자면 1, 숫자면 0 출력 
	if ((char)s[0] >= '0' && (char)s[0] <= '9') {
		return 0;
	}
	else {
		return 1;
	}
}




void main() {
	char ch;
	int i; // 포문이나 임시로 무언가 카운팅이 필요할때 사용합니다.
	int* x = (int*)malloc(sizeof(int));

	NODE* node = NULL; // 마지막 쓴 노드의 주소를 저장한다.
	NODE* temp = NULL; // Linked list 속에서 위치 이동 역할을 한다.


	FILE* file = NULL;
	errno_t err = fopen_s(&file, "student.txt", "rt"); // student.txt 파일을 읽습니다.

	i = 1; // 리스트 초기화에 임시로 사용
		   //파일에서 값을 임시로 저장할 변수를 정합니다.
	char* temp_name[20];
	unsigned long temp_sid;
	//
	while (!feof(file)) {

		fscanf_s(file, "%d %s", &temp_sid, temp_name, 20);
		//linked list 초기화
		if (i == 1) {
			head = CreateNode(temp_name, temp_sid);
			node = head;//노드의 초기 값을 head위치 주소로 정한다.(링크를 위해)
		}
		else {
			temp = node; // 이전 노드위치 임시저장
			node = CreateNode(temp_name, temp_sid);
			//링크 연결하기
			temp->link = node; // 이전 노드의 링크를 새로운 노드 주소값으로 등록한다.
		}
		i++;
	}
	printf("input.txt로 받은 입력값을 변환하시겠습니까?(y/n)");

	// input.txt 입력 받아서 결과값을 커맨드 라인에 출력
	scanf_s("%c", &ch); getchar();
	if (ch == 'y') {
		ChangeTo();
	}
	//

	Clear(head); // 모든 Linked list를 초기화 시킵니다.
	scanf_s("%c", &ch); getchar();
}

