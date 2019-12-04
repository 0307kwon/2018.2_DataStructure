#define StringSize 20
#define LineSize 200
#include <stdio.h>

typedef struct Hnode {
	void* dataPtr;
	int freq; //소스코드에서 등장한횟수를 뜻합니다.
	struct Hnode* next;// collision 방지용입니다.
}HNODE;

typedef struct {
	HNODE* hTable;
	int (*ReturnHAddress)(void* data, int maxSize); // Hash의 주소를 반환해주는 함수 (인자1 = 데이터, 인자2 = 데이터 타입)
	int(*Compare)(void* data1, void* data2); // 데이터 비교 함수
	char dataType;
	int maxSize;
	int NodeNumber; // 안에 들어있는 노드의 수 ,heap만들때 씁니다.
}HTABLE;

int _AddressString(void* data,int max);//hash의 주소를 반환해주는 함수 (String 버전) (인자1 :데이터, 인자2 : 헤쉬 MAXsize)
int _CompareString(void* data1, void* data2); // 데이터 비교 함수
HTABLE* _CreateHash(char dataType, int maxSize); //해쉬를 만드는 함수
int _InsertHash(HTABLE* hash, void* dataPtr); // 해쉬에 값을 넣는 함수
void* _MakeDataPtr(void* dataPtr, char dataType);//데이터 멜록하고 주소값 반환(데이터가 사라지지않도록 하는것)
void _PrintHash(HTABLE* hash); // 해쉬 안의 값을 모두 printf 하는 함수
int KeywordToHash(FILE* ex1, HTABLE* hash); // 읽어온 파일에서 모든 키워드를 해쉬에 저장하는 함수
void FreeHash(HTABLE* hash); // 해쉬를 free 시키는 함수