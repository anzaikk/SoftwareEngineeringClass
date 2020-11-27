#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void CharCount(char *file); //�����ж��ٸ��ַ�
void WordCount(char *file); //��ȡ�ж��ٸ����� 
void LineCount(char *file); //��ȡ�ж����� 

int main(int argc,char *argv[])
{
	if(argc>3){
		printf("�����������ֻ������������������ȷ������ʾ����wc.exe -c �ļ���");
	}else{
		if(!(strcmp(argv[1],"-c")))
			CharCount(argv[2]);	 
		else if(!(strcmp(argv[1],"-w")))
			WordCount(argv[2]); 
		else if(!(strcmp(argv[1],"-l")))
			LineCount(argv[2]); 
		else
			printf("�����������ֻ��-c,-w,-l�ĸ�����"); 
	}
	return 0;
}

void CharCount(char *file)//�ַ�ͳ��
{
	FILE *qr = fopen(file, "r");
	int sum = 0; 
	while(fgetc(qr) != EOF)
		sum++;
	printf("the count of char is ��%d.\n",sum-1); //
	fclose(qr);
}

void WordCount(char *file)//����ͳ��
{
	FILE *qr = fopen(file, "r");
	int sum = 0;
	char character = fgetc(qr);
	//ÿ�����ʵ����ַ�һ����[A-Z][a-z][0-9] ֮�䣬��һ���������ַ���[A-Z][a-z][0-9] ֮���Ǽ�������һ�� 
	while(character != EOF)
	{
		if((character >= 'a'&&character <= 'z')||(character >= 'A'&&character <='Z')||(character >= '0'&&character <= '9')){
			sum++;
			character = fgetc(qr);
			while((character >= 'a'&&character <= 'z')||(character >= 'A'&&character <='Z')||(character >= '0'&&character <= '9'))
				character = fgetc(qr); //����һ���ַ��� [A-Z][a-z][0-9] ֮�䣬��������while���� �� 
		}else{
			character=fgetc(qr);
		}
	}
	printf("the count of word is ��%d.\n",sum);
	fclose(qr);
}

void LineCount(char *file)//����ͳ�ơ� 
{
	FILE *qr = fopen(file, "r");
	char character = fgetc(qr);
	int sum = 1;
	while(character != EOF){
		if (character == '\n') //�򵥵��ж϶������ַ��Ƿ���\n��ʵ���ˡ� 
			sum ++;
		character = fgetc(qr);
	}
	printf("the count of line is ��%d.\n",sum-1);
	fclose(qr);
}


