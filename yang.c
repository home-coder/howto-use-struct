#include <stdio.h>

struct yangst {
	char *name;
	char no;
	int  age;
	char wife[32];
	int  big_year[30]; //1954
	char *partners[10];
	int  parttime[2][10];//{{1956， 1957， 1958},{1963， 1964}， };
};

static void print_yang(struct yangst yznlife, int (*ppt)[10])
{
	int bylen = sizeof(yznlife.big_year)/sizeof(yznlife.big_year[0]);
	int pnlen = sizeof(yznlife.partners)/sizeof(yznlife.partners[0]);

	printf("name = %s\n", yznlife.name);
	printf("no   = %c\n", yznlife.no);
	printf("age  = %d\n", yznlife.age);
	printf("wife = %s\n", yznlife.wife);
	printf("big_year = ");

	/*print big year*/
	int i = 0;

	for (; i < bylen; i++) {
		if (yznlife.big_year[i] == -0xff) {
			break;
		}
		printf("%d,", yznlife.big_year[i]);
	}
	printf("\n");

	/*print parttime, 使用行指针会将结果处理的很漂亮*/
	int ptrow = sizeof(yznlife.parttime)/sizeof(yznlife.parttime[0]);
	int ptcol = sizeof(yznlife.parttime[0]);
	//	typedef int (*pparttime)[ptcol];
	int j;
	for (i = 0; i < ptrow; i++) {
		for (j = 0; j < ptcol; j++) {
			if ( *(*(ppt + i) + j) == -0xff ) {
				break;
			}
			printf("%d, ", *(*(ppt + i) + j));
		}
	}

	printf("\n-------------------------------------\n");
}

static void print_yang2(struct yangst yznlife)
{
	int bylen = sizeof(yznlife.big_year)/sizeof(yznlife.big_year[0]);
	int pnlen = sizeof(yznlife.partners)/sizeof(yznlife.partners[0]);

	printf("name = %s\n", yznlife.name);
	printf("no   = %c\n", yznlife.no);
	printf("age  = %d\n", yznlife.age);
	printf("wife = %s\n", yznlife.wife);
	printf("big_year = ");

	/*print big year*/
	int i = 0;

	for (; i < bylen; i++) {
		if (yznlife.big_year[i] == -0xff) {
			break;
		}
		printf("%d,", yznlife.big_year[i]);
	}
	printf("\n");

	/*print partner time*/
	int ptrow = sizeof(yznlife.parttime)/sizeof(yznlife.parttime[0]);
	int ptcol = sizeof(yznlife.parttime[0]);
	int j;
	for (i = 0; i < ptrow; i++) {
		for (j = 0; j < ptcol; j++) {
			if ( yznlife.parttime[i][j] == -0xff ) {
				break;
			}
			printf("%d, ", yznlife.parttime[i][j]);
		}
	}

	printf("\n-------------------------------------\n");
}

int main()
{
//1.0 声明时初始化结构体，不包含赋值操作
	{
		struct yangst yznlife = {
			.name = "Yangzhenning",
			.no   = 'A',
			.age  = 95,
			.wife = "Duzhili",
			.big_year = {1942, 1954, 1966, 1971, 2003, -0xff},
			.partners = {"Mils", "Lizhengdao", "Wengfan", NULL},
			.parttime = {{1956, 1957, 1958, -0xff}, {1963, 1964, -0xff}},
		};

		typedef int (*pptime)[10];
		pptime ppt = yznlife.parttime;
		print_yang(yznlife, ppt);
	}
//1.1 声明时初始化结构体，不包含赋值操作, 不使用行指针也是可以做到的，也很漂亮啊
	{
		struct yangst yznlife = {
			.name = "Yangzhenning",
			.no   = 'A',
			.age  = 95,
			.wife = "Duzhili",
			.big_year = {1942, 1954, 1966, 1971, 2003, -0xff},
			.partners = {"Mils", "Lizhengdao", "Wengfan", NULL},
			.parttime = {{1956, 1957, 1958, -0xff}, {1963, 1964, -0xff}},
		};

		print_yang2(yznlife);
	}

	return 0;
}
