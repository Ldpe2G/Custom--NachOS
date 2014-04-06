#include "syscall.h"

/* ����һ����������λ�� */
#define	INT_MAX_DIGIT_NUM	5

/**********************************************************
��������
	IntToChar
��Σ�
	InputInt��Ҫת�����ַ���������
���Σ�
	OutputChar��ת������ַ���
���ܣ�
	������ת��Ϊ�ַ���
**********************************************************/
unsigned int IntToChar(char* OutputChar, unsigned int InputInt){
	unsigned int CharNum = 0;
	unsigned int digit, i;
	char* pChar = OutputChar + INT_MAX_DIGIT_NUM;
	/* ������ת��Ϊ�ַ���*/
	do{
		pChar--;
		CharNum++;
		digit = (char)(InputInt % 10) + '0';
		InputInt = InputInt / 10;
		*pChar = digit;
	}while (InputInt > 0);

	/* ���ַ����Ƶ����鿪ͷ */
	for (i=0; i<CharNum; i++){
		*OutputChar = *pChar;
		OutputChar++;
		pChar++;
	}
	*OutputChar = 0;
	return CharNum;
}

#define SIZE (10)

/*��Ҫ���������*/
unsigned int A[SIZE] = {89, 65, 789, 985, 3254, 456, 5241, 235, 4521, 3201};

//�����������������ϳ�һ����������
unsigned int* merge(unsigned int* array1, int length1, unsigned int* array2, int length2){
  unsigned int result[length1 + length2];
  int i = 0, j = 0;
  int index = 0;
  while(i < length1 && j < length2){
    if(array1[i] < array2[j])
      result[index ++] = array1[i ++];
    else
      result[index ++] = array2[j ++];
  }
  for(; i < length1; i++)
    result[index ++] = array1[i];
  for(; j < length2; j++)
    result[index ++] = array2[j];
  return result;
}

//����start��endȷ���ķ�Χ��ȡarray����
unsigned int* takeN(unsigned int* array, int start, int end){
  unsigned int temp[end - start + 1];
  int i = start;
  for(; i <= end; i++)
    temp[i - start] = array[i];
  return temp;
}

unsigned int* mergeSort(unsigned int* array, int length){
  int n = length / 2;
  if(n == 0)
    return array;
  else{
    //���������൱�ڰ�array����ֳ�������
    unsigned int* temp1 = takeN(array, 0, n - 1);
    unsigned int* temp2 = takeN(array, n, length - 1);
    return merge(mergeSort(temp1, n), n, mergeSort(temp2, length - n), length - n);
  }
}


int main(){
	int i, j, tmp;
	char IntChar[6];
	unsigned int CharNum;

	Write("�鲢����ǰ����˳��\n", 17, ConsoleOutput);
	/*��˳����������е�����*/
	for (i=0; i<SIZE; i++){
		CharNum = IntToChar(IntChar, A[i]);
		Write(IntChar, CharNum, ConsoleOutput);
		Write(" ", 1, ConsoleOutput);
	}
	Write("\n", 1, ConsoleOutput);
	
	/*�鲢����*/
	merge_sort();

	Write("�鲢���������˳��\n", 17, ConsoleOutput);
	/*��˳����������е�����*/
	for (i=0; i<SIZE; i++){
		CharNum = IntToChar(IntChar, A[i]);
		Write(IntChar, CharNum, ConsoleOutput);
		Write(" ", 1, ConsoleOutput);
	}
	Write("\n\n", 2, ConsoleOutput);
}
