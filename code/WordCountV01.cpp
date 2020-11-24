#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void CharCount(char *file); //�����ж��ٸ��ַ�
void WordCount(char *file); //��ȡ�ж��ٸ����� 
void LineCount(char *file); //��ȡ�ж����� 
void MuiltipleCount(char *file); //��ȡ�ж��ٴ����У��հ��У�ע���� 

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
		else if(!(strcmp(argv[1],"-a")))
			MuiltipleCount(argv[2]);
		else
			printf("�����������ֻ��-l,-w,-l,-a�ĸ�����"); 
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

void MuiltipleCount(char *file)//�����У�����ͳ�ƣ�ע���С� ��������Ϊ�����ı�־ ,ע��Ҫ����һ�в����ڴ�������� �� �ļ���һ�в�Ϊ�ա� 
{
	FILE *qr = fopen(file, "r");
	char ch = fgetc(qr);
	int LBraces = 0, RBraces = 0;//ͳ�����Ҵ����Ÿ��� 
	int c=0,e=0,n=0;
	while(ch != EOF)
	{
		if(ch == '{') LBraces++; 
		else if(ch == '\n'){
			ch = fgetc(qr);
				while(ch == '\n'){ //���������ǻ�����ô�հ��м�һ�� 
					e++;
					ch = fgetc(qr);
				}
		}else{
			ch = fgetc(qr);
		} 
		while(LBraces!=RBraces&&LBraces!=0){//�������Ų����ڴ������Ÿ���ʱ���ڴ��� ������档
			if (ch == '\n'){ //���������С� 
				ch = fgetc(qr);
				while(ch == '\n'){ //���������ǻ�����ô�հ��м�һ�� 
					e++;
					ch = fgetc(qr);
				}
				while(ch == '\0') ch=fgetc(qr); 
				if(ch == '/'){
					ch=fgetc(qr); 
					if (ch == '/'){
						n++;
						while(ch != '\n')
							ch = fgetc(qr);					
					}
				}else{
					c++;
				} 
			}else{
				ch=fgetc(qr);				
			}
			if(ch == '{') LBraces++;
			else if(ch == '}') RBraces++;
		}
		
	}
	printf("the count of code line is ��%d.\n",c+1);//���ϴ�����־��{��,"}"������ 
	printf("the count of empt line is ��%d.\n",e);
	printf("the count of note line is ��%d.\n",n);
	fclose(qr);
}

