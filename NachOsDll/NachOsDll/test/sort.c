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
unsigned int IntToChar(char* OutputChar, unsigned int InputInt)
{
	unsigned int CharNum = 0;
	unsigned int digit, i;
	char* pChar = OutputChar + INT_MAX_DIGIT_NUM;
	/* ������ת��Ϊ�ַ���*/
	do
	{
		pChar--;
		CharNum++;
		digit = (char)(InputInt % 10) + '0';
		InputInt = InputInt / 10;
		*pChar = digit;
	}
	while (InputInt > 0);

	/* ���ַ����Ƶ����鿪ͷ */
	for (i=0; i<CharNum; i++)
	{
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

int main()
{
	int i, j, tmp;
	char IntChar[6];
	unsigned int CharNum;

	Write("����ǰ����˳��\n", 17, ConsoleOutput);
	/*��˳����������е�����*/
	for (i=0; i<SIZE; i++)
	{
		CharNum = IntToChar(IntChar, A[i]);
		Write(IntChar, CharNum, ConsoleOutput);
		Write(" ", 1, ConsoleOutput);
	}
	Write("\n", 1, ConsoleOutput);
	/*����*/
	for (i=0; i<SIZE; i++)
	{
		for (j=0; j<(SIZE-1); j++)
		{
			if (A[j] > A[j+1])
			{	/* out of order -> need to swap ! */
				tmp = A[j];
				A[j] = A[j+1];
				A[j+1] = tmp;
			}
		}
	}
	Write("���������˳��\n", 17, ConsoleOutput);
	/*��˳����������е�����*/
	for (i=0; i<SIZE; i++)
	{
		CharNum = IntToChar(IntChar, A[i]);
		Write(IntChar, CharNum, ConsoleOutput);
		Write(" ", 1, ConsoleOutput);
	}
	Write("\n\n", 2, ConsoleOutput);
}
