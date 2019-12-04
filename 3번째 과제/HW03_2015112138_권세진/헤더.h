#pragma once
#include <stdio.h>
#include <time.h>
typedef struct ManNode {
	char name[20];
	int bullet;
	struct ManNode* next;
}ManNode;


typedef struct Head {
	int count;
	ManNode* head;
}Head;


int Random(int a) {// 1부터 a까지
	return rand() % a + 1;
}

Head* CreateHead() { // 헤드를 만듭니다.
	Head* head = (Head*)malloc(sizeof(Head));
	if (head == NULL) {
		return NULL;
	}
	head->count = 0;
	head->head = NULL;
	return head;
}

int InsertNode(Head* head, int distance, char name[20],int bullet) { // distance가 0이면 마지막 노드에 추가됨,distnace가 n이면 위치 n뒤에 추가됨,0반환 실패,1반환 성공
	ManNode* Fnode;
	ManNode* Nnode;

	//새로운 노드 초기화
	ManNode* newNode = (ManNode*)malloc(sizeof(ManNode));
	if (newNode == NULL) {
		return 0;
	}
	strcpy_s(newNode->name,20,name,20);
	newNode->bullet = bullet;
	newNode->next = NULL;


	if (distance == 0 || distance == head->count) {
		//마지막 노드에 추가할때
		if (head->head == NULL) {
			head->head = newNode;
			newNode->next = newNode; // 마지막노드 첫번째랑 연결
		}
		else {
			Fnode = head->head;
			for (int i = 0; i < head->count - 1; i++) {
				Fnode = Fnode->next;
			}// 마지막 노드를 가리킴
			Nnode = Fnode->next;//마지막 노드의 다음노드 가리킴
			Fnode->next = newNode;
			newNode->next = Nnode; // 마지막노드 첫번째랑 연결 
		}
	}
	else {
		//사이에 추가할때
		Fnode = head->head;
		for (int i = 0; i < distance - 1; i++) {
			Fnode = Fnode->next;
		}
		Nnode = Fnode->next;
		Fnode->next = newNode;
		newNode->next = Nnode;
	}
	head->count++;
	return 1;
}

void PrintALL(Head* head) {
	ManNode* temp = head->head;
	if (head->head != NULL) {
		for (int i = 0; i < 10; i++) {
			if (i == head->count - 1) {
				printf("%d번째 게임에서 %d번째 총알을 맞아 %s(이)가 사망했습니다. \n----- 게임끝 -----\n", i+1, temp->bullet, temp->name);
				temp = temp->next;
			}
			else {
				printf("%d번째 게임에서 %d번째 총알을 맞아 %s(이)가 사망했습니다.\n", i+1, temp->bullet, temp->name);
				temp = temp->next;
			}
		}
	}
}

int DeleteMan(Head* head, int distance, char* returnS[20]) { // int는 무조건 1이상이여야합니다. 실패 리턴 0,returnS는 지워진 사람 이름리턴받을 스트링
	ManNode* Fnode = NULL;
	ManNode* Target = NULL;
	ManNode* Nnode = NULL;
	if (distance < 1) {
		return 0;
	}

	// 제일 첫번째 노드 지우는 경우, 나머지 경우.

	//첫번째
	if (head->count != 1) {
		if (distance == 1 || distance % (head->count) == 1) {// 전체크기 8인데 9걸리면 1걸리는거랑 똑같음

			Fnode = head->head;
			for (int i = 0; i < head->count - 1; i++) {
				Fnode = Fnode->next;
			}//마지막 노드 가리킴
			Target = head->head;
			Nnode = Target->next;

			strcpy_s(returnS, 20, Target->name, 20);

			//삭제하고 다시연결
			free(Target);
			head->head = Nnode;
			Fnode->next = Nnode;


		}
		else {
			Fnode = head->head;
			for (int i = 0; i < distance - 2; i++) {
				Fnode = Fnode->next;
			}// 거리보다 1 앞에 있는 노드 검색
			Target = Fnode->next;
			Nnode = Target->next;

			strcpy_s(returnS, 20, Target->name, 20);

			free(Target);
			Fnode->next = Nnode;



		}
	}
	else {
		strcpy_s(returnS, 20, head->head->name, 20);
		head->head = NULL;
	}
	head->count--;
}

