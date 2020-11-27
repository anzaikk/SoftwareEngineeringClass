#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int CharCount(char* file)//只统计英文和数字字符
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

int WordCount(char* file)//单词统计
{
	FILE* qr = fopen(file, "r");
	int sum = 0;
	char character = fgetc(qr);
	//每个单词的首字符一定在[A-Z][a-z] 之间，第一次碰到的字符在[A-Z][a-z]之间是计数器加1。 
	while (character != EOF)
	{
		if ((character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z') ) {
			sum++;
			character = fgetc(qr);
			while ((character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z'))
				character = fgetc(qr); //当下一个字符在 [A-Z][a-z] 之间，就锁定在while里面 。 
		}
		else {
			character = fgetc(qr);
		}
	}
	fclose(qr);
	return sum;
}

int LineCount(char* file)//行数统计。 
{
	FILE* qr = fopen(file, "r");
	char character = fgetc(qr);
	int sum = 1;
	while (character != EOF) {
		if (character == '\n') //简单的判断读出的字符是否是\n就实现了。 
			sum++;
		character = fgetc(qr);
	}
	fclose(qr);
	return sum;
}

int* MuiltipleCount(char* file)//代码行，空行统计，注释行。 大括号作为代码块的标志 ,注释要另起一行并且在代码块里面 。 文件第一行不为空。 
{
	FILE* qr = fopen(file, "r");
	int *re;//设置测试的标志
	re = (int*)malloc(sizeof(int)*3);//由于返回数组要一个连续的空间
	char character = fgetc(qr);
	int LBraces = 0, RBraces = 0;//统计左右大括号个数 
	int c = 0, e = 0, n = 0;
	while (character != EOF) {
		if (character == '{') LBraces++;
		else if (character == '\n') {
			character = fgetc(qr);
			while (character == '\n') { //若连续都是换行那么空白行加一。 
				e++;
				character = fgetc(qr);
			}
		}
		else {
			character = fgetc(qr);
		}
		while (LBraces != RBraces && LBraces != 0) {//大左括号不等于大右括号个数时，在代码 语句里面。
			if (character == '\n') { //当遇到换行。 
				character = fgetc(qr);
				if (character == '\n') { //若连续都是换行那么空白行加一。 
					while (character == '\n') {
						e++;
						character = fgetc(qr);
					}
					c++;
				}else {
					c++;
				}
			}else if (character == '/') {//注释只能在直接在代码后面写情况
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
	re[1] = c-n-1;//不算上代码块标志“{”"这一行 ,代码逻辑这个c在有注释的时候多加了1
	re[2] = e;
	re[3] = n;
	return re;
}

