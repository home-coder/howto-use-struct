#include <stdio.h>

int main()
{
//1. struct 的声明定义
	{
		struct yangst {
			char *name;
			char no;
			int  age;
			char wife[];
			int  big_year[]; //1954
			char *partners[];
			int  parttime[][];//{{1956， 1957， 1958},{1963， 1964}， };
		};

	}

	return 0;
}
