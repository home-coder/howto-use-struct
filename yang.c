#include <stdio.h>

struct yangst {
	char *name;
	char no;
	int  age;
	char wife[32];
	int  big_year[30]; //1954
	char *partners[10];
	int  parttime[][10];//{{1956， 1957， 1958},{1963， 1964}， };
};

static void print_yang(struct yangst yznlife)
{
	int bylen = sizeof(yznlife.big_year)/sizeof(yznlife.big_year[0]);
	int pnlen = sizeof(yznlife.partners)/sizeof(yznlife.partners[0]);

	printf("name = %s\n", yznlife.name);
	printf("no   = %c\n", yznlife.no);
	printf("age  = %d\n", yznlife.age);
	printf("wife = %s\n", yznlife.wife);
	printf("big_year = ");
	int i = 0;
	for (; i < bylen; i++) {
		if (yznlife.big_year[i] == -0xff) {
			break;
		}
		printf("%d,", yznlife.big_year[i]);
	}
	printf("\n");

}

int main()
{
//1.0 初始化结构体，不包含赋值操作
	{
		struct yangst yznlife = {
			.name = "Yangzhenning",
			.no   = 'A',
			.age  = 95,
			.wife = "Duzhili",
			.big_year = {1942, 1954, 1966, 1971, 2003, -0xff},
			.partners = {"Mils", "Lizhengdao", "Wengfan", NULL},
			//.parttime = {{1956, 1957, 1958}, {1963, 1964}},
		};

		print_yang(yznlife);
	}

	return 0;
}
