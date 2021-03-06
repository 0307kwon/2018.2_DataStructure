#include "hash.h"

int _AddressString(void* data, int max) {//hash의 주소를 반환해주는 함수 (String 버전) (인자1 :데이터, 인자2 : 헤쉬 MAXsize)
	if (data != NULL) {
		int length = strlen((char*)data);
		int add = 0;
		for (int i = 0; i < length; i++) {
			add += ((char*)data)[i]; // 주소 반환값의 다양화를 위해서 string 배열의 모든 아스키 코드값 더함
		}
		return (add % max);
	}
}

void* _MakeDataPtr(void* dataPtr, char dataType) {//데이터 멜록하고 주소값 반환(데이터가 사라지지않도록 하는것)
	if (dataType == 'S') {
		int length = strlen((char*)dataPtr);
		char* newData = (char*)malloc(sizeof(char)*length);
		if (newData == NULL) {
			return NULL;
		}
		strcpy(newData,dataPtr);
		return newData;
	}
}

int _CompareString(void* data1, void* data2) { // 스트링 데이터 비교 함수 같으면 1반환
	return !strcmp((char*)data1, (char*)data2);
}

int KeywordToHash(FILE* ex1, HTABLE* hash) { // 헤쉬에 키워드 집어넣는 함수
	char string_t[LineSize]; // 한줄 읽은값
	char* temp_t = NULL; // 토큰 나눈값
	char* context = NULL; //strtok 쓰기위해 필요한 널포인터 // 짜르고 남은 문자열
	char* delimiter = " \t\n(){}=;<>+-,[].!";
	while (!feof(ex1)) {

		fgets(string_t, LineSize, ex1);
		temp_t = strtok_s(string_t, delimiter, &context);
		while (temp_t != NULL) {
			if (temp_t[0] == '/' && temp_t[1] == '/') {// 그 줄에서 주석부분은 그냥 넘김
				break;
			}
			else if (temp_t[0] == '\"' || temp_t[0] == '\'' || temp_t[0] == -95) {//""큰따옴표나 작은따옴표는 넘깁니다. || 뒷부분은 한글 유형의 큰따옴표도 거르기 위해 쓴것임
				int i = 1;
				while (temp_t[i] != '\"' && temp_t[i] != '\'' && temp_t[i] != -95 && &temp_t[i] != &string_t[LineSize]) { // 마치는 큰따옴표를 찾습니다.
					i++;
				}
				//다음 토큰 누락을 막기위한 대책
				if (temp_t[i] == -95) { // 한글유형의 큰따옴표인경우 2바이트이기때문에
					i += 2;//2바이트 더해줌
				}
				else {//아니면 1바이트이기 때문에
					i += 1;//1바이트 더해줌
				}
				temp_t[i] = ')'; //printf(“%d()\n”, a); 여기서 쉼표가 그전 토큰 사용에서 NULL로 설정되기 때문에 다시 토큰으로 만들어주어야한다.
								 //
				temp_t = strtok_s(&temp_t[i], delimiter, &context);// 다음 짜르는 위치를 큰타옴표 끝나고 다음위치로 지정

			}
			else {
				_InsertHash(hash, temp_t);
				temp_t = strtok_s(NULL, delimiter, &context);
			}
		}
	}
	return 1;
}

int _InsertHash(HTABLE* hash, void* dataPtr) {
	hash->NodeNumber++; // 노드수 증가

	int address = hash->ReturnHAddress(dataPtr, hash->maxSize); // 주소반환
	if (hash->hTable[address].dataPtr == NULL) {
		hash->hTable[address].dataPtr = _MakeDataPtr(dataPtr, hash->dataType);//데이터 멜록하고 주소값 반환
		hash->hTable[address].freq = 1;
		hash->hTable[address].next = NULL;
		return 1;
	}
	else { // collision 발생

		//충돌일으킨 위치의 노드들 중 들어온 데이터와 같은 값이 있는지 체크합니다.
		
		if (hash->Compare(dataPtr, hash->hTable[address].dataPtr)) { // 들어온데이터와 충돌일으킨 데이터가 같은 값이면(첫번째위치 체크)
			hash->hTable[address].freq++;
			return 1;
		}
		HNODE* temp = &(hash->hTable[address]);
		while (temp->next != NULL) {
			if (hash->Compare(dataPtr, temp->next->dataPtr)) { // 들어온데이터와 충돌일으킨 데이터가 같은 값이면(나머지 위치 체크)
				temp->next->freq++;
				return 1;
			}
			temp = temp->next;
		}
		//여기 이후로 진행이 계속되면 같은 데이터가 없다는 뜻이므로 새로운 노드 생성해서 뒤에 붙임
		HNODE* newNode = (HNODE*)malloc(sizeof(HNODE)); // 새로운 노드 생성하고 뒤에 붙임
		if (!newNode) {
			return NULL;
		}
		newNode->dataPtr = _MakeDataPtr(dataPtr, hash->dataType);//들어온 문자열 길이와 같은 길이의 문자열 멜록으로 만들고 집어넣고 주소값 반환
		newNode->freq = 1;
		newNode->next = NULL;
		temp->next = newNode; // 여기서 temp는 위에서 쓴 temp, 마지막 노드위치를 가리키고있다. 즉 마지막 노드뒤에 새로운 노드 붙임.
		return 1;
	}
	
}


HTABLE* _CreateHash(char dataType, int maxSize) {
	if (dataType == 'S') {
		HTABLE* hash = (HTABLE*)malloc(sizeof(HTABLE));
		if (hash == NULL) {
			return NULL;
		}
		hash->hTable = (HNODE*)calloc(maxSize, sizeof(HNODE));
		if (hash->hTable == NULL) {
			return NULL;
		}
		hash->ReturnHAddress = _AddressString;
		hash->Compare = _CompareString;
		hash->dataType = 'S';
		hash->NodeNumber = 0;
		hash->maxSize = maxSize;
	}
}

void _PrintHash(HTABLE* hash) {
	if (hash->dataType = 'S') {
		for (int i = 0; i < hash->maxSize; i++) {
			printf("%d : %s (%d) ", i, (char*)(hash->hTable[i].dataPtr), hash->hTable[i].freq);

			if (hash->hTable[i].next != NULL) { // collision때문에 붙은 뒷꽁무늬가 있으면 다 print
				HNODE* temp = &(hash->hTable[i]);
				while (temp->next != NULL) {
					printf("-> %s (%d)", (char*)(temp->next->dataPtr), temp->next->freq);
					temp = temp->next;
				}
			}
			printf("\n");
		}
	}
}
void _FreeHash_LinkedList(HNODE* node) {
	if (node->next != NULL) {
		_FreeHash_LinkedList(node->next);
		free(node);
		return;
	}
	else {
		free(node);
		return;
	}
}

void FreeHash(HTABLE* hash) {
	//collision 때문에 뒤에 붙어있는 노드부터 제거
	for (int i = 0; i < hash->maxSize; i++) {
		if (hash->hTable[i].next != NULL) {
			_FreeHash_LinkedList(hash->hTable[i].next); // 재귀함수를 이용해서 뒤에 붙어있는 linked list 제거
		}
	}
	//그 이후 hashTable =>free
	free(hash->hTable);
}

