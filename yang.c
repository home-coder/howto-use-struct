#include <stdio.h>

int main()
{
//1. struct 的声明定义
	{
		struct yangst {
			char *name;
			char no;
			int  age;
			char wife[32];
			int  big_year[30]; //1954
			char *partners[10];
			int  parttime[][10];//{{1956， 1957， 1958},{1963， 1964}， };
		};

	}

	return 0;
}
