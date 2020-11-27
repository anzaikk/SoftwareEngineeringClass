#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int CharCount(char* file)//ֻͳ��Ӣ�ĺ������ַ�
{
	FILE* qr = fopen(file, "r");
	int sum = 0;
	char character = fgetc(qr);
	while (character != EOF) {
		if ((character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z') || (character >= '0' && character <= '9'))
			sum++;
		character = fgetc(qr);
	}
	fclose(qr);
	return sum;
}

int WordCount(char* file)//����ͳ��
{
	FILE* qr = fopen(file, "r");
	int sum = 0;
	char character = fgetc(qr);
	//ÿ�����ʵ����ַ�һ����[A-Z][a-z] ֮�䣬��һ���������ַ���[A-Z][a-z]֮���Ǽ�������1�� 
	while (character != EOF)
	{
		if ((character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z') ) {
			sum++;
			character = fgetc(qr);
			while ((character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z'))
				character = fgetc(qr); //����һ���ַ��� [A-Z][a-z] ֮�䣬��������while���� �� 
		}
		else {
			character = fgetc(qr);
		}
	}
	fclose(qr);
	return sum;
}

int LineCount(char* file)//����ͳ�ơ� 
{
	FILE* qr = fopen(file, "r");
	char character = fgetc(qr);
	int sum = 1;
	while (character != EOF) {
		if (character == '\n') //�򵥵��ж϶������ַ��Ƿ���\n��ʵ���ˡ� 
			sum++;
		character = fgetc(qr);
	}
	fclose(qr);
	return sum;
}

int* MuiltipleCount(char* file)//�����У�����ͳ�ƣ�ע���С� ��������Ϊ�����ı�־ ,ע��Ҫ����һ�в����ڴ�������� �� �ļ���һ�в�Ϊ�ա� 
{
	FILE* qr = fopen(file, "r");
	int *re;//���ò��Եı�־
	re = (int*)malloc(sizeof(int)*3);//���ڷ�������Ҫһ�������Ŀռ�
	char character = fgetc(qr);
	int LBraces = 0, RBraces = 0;//ͳ�����Ҵ����Ÿ��� 
	int c = 0, e = 0, n = 0;
	while (character != EOF) {
		if (character == '{') LBraces++;
		else if (character == '\n') {
			character = fgetc(qr);
			while (character == '\n') { //���������ǻ�����ô�հ��м�һ�� 
				e++;
				character = fgetc(qr);
			}
		}
		else {
			character = fgetc(qr);
		}
		while (LBraces != RBraces && LBraces != 0) {//�������Ų����ڴ������Ÿ���ʱ���ڴ��� ������档
			if (character == '\n') { //���������С� 
				character = fgetc(qr);
				if (character == '\n') { //���������ǻ�����ô�հ��м�һ�� 
					while (character == '\n') {
						e++;
						character = fgetc(qr);
					}
					c++;
				}else {
					c++;
				}
			}else if (character == '/') {//ע��ֻ����ֱ���ڴ������д���
				character = fgetc(qr);
				if (character == '/') {
					n++;
					c++;
					while (character != '\n')
						character = fgetc(qr);
				}
			}else {
				character = fgetc(qr);
			}
			if (character == '{') LBraces++;
			else if (character == '}') RBraces++;
		}
	}
	fclose(qr);
	re[1] = c-n-1;//�����ϴ�����־��{��"��һ�� ,�����߼����c����ע�͵�ʱ������1
	re[2] = e;
	re[3] = n;
	return re;
}

