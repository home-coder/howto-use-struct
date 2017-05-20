#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct yangst {
	char *name;
	char no;
	int  age;
	char wife[32];
	int  big_year[30]; //1954
	char *partners[10];
	int  parttime[2][10];//{{1956， 1957， 1958},{1963， 1964}， };
};

#define	MARRIAGE     3  //最多3段婚姻
#define REGION		 2  //时间跨度范围
struct his_wife {
	char *name;
	int love_years[REGION];
	int year;
	int wife_big[20];
};

struct physicalst {
	struct his_wife wife[MARRIAGE];
	int big_year[20];
};

typedef enum {false = 0, true}bool;

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

static void print_yang_point(struct yangst *pyzn)
{
	printf("name = %s\n", pyzn->name);
	printf("no   = %c\n", pyzn->no);
	printf("age  = %d\n", pyzn->age);
	printf("wife = %s\n", pyzn->wife);
	printf("big_year = ");

	/*print big year*/
	int bylen = sizeof(pyzn->big_year)/sizeof(pyzn->big_year[0]);
	int *pby = pyzn->big_year;
	for (; (pby < pyzn->big_year+bylen) && (*pby != -0xff); pby++) {
		printf("%d,", *pby);
	}
	printf("\n");

	/*print partner time*/
	int ptrow = sizeof(pyzn->parttime)/sizeof(pyzn->parttime[0]);
	int ptcol = sizeof(pyzn->parttime[0]);
	int i = 0, j = 0;
	for (; i < ptrow; i++) {
		for (j = 0; j < ptcol; j++) {
			if ( pyzn->parttime[i][j] == -0xff ) {
				break;
			}
			printf("%d, ", pyzn->parttime[i][j]);
		}
	}

	printf("\n-------------------------------------\n");
}
#define debug() printf("%s %d\n", __func__, __LINE__)
static int query_big_year(struct yangst *pyzn, char *pter, int *ptime, int plen)
{
	char **yznpter = pyzn->partners;
//	char *yznpter = pyzn->partners[0];
	bool flag = false;

	/*
	*将dst数组所有元素与src中的每一行数据比较，如果匹配到最后，dst数组的个数到头了，并且src的下一个元素是-0xff 同时j == plen被查询数组到头了
	*那么完成查询动作
	*
	*/
	int ptrow = sizeof(pyzn->parttime)/sizeof(pyzn->parttime[0]);
	int ptcol = sizeof(pyzn->parttime[0]);
	if ( ptcol-1 < plen) {
		printf("src列数组长度太小了，退出查询\n");
		return -1;
	}

	for (; *yznpter != NULL; yznpter++) {
		if ( !strncmp(pter, *yznpter, strlen(pter)) ) {
			int i = 0, j = 0;
			for (i = 0; i < ptrow; i++) {
				for (j = 0; j < plen; j++) {
					if (pyzn->parttime[i][j] == -0xff || ptime[j] == -0xff) {
						break;
					}
					if (pyzn->parttime[i][j] != ptime[j]) {
						break;
					}
				}
				if ( (j == plen) && (pyzn->parttime[i][j] == -0xff) ) {
					/*query big year*/
					int *pby = pyzn->big_year;
					for (; *pby != -0xff; pby++) {
						for (j = 0; j < plen; j++) {
							if (*pby == ptime[j]) {
								printf("have find big year is %d with %s \n", *pby, pter);
								flag = true;
							}
						}
					}
				}
			}
		}
	}
	printf("-------------------------------------\n");

	return flag;
}

static void query_who_every_bigyear(struct physicalst yznlife)
{
	int i = 0, j = 0;

	for (i = 0; yznlife.big_year[i] != -0xff; i++) {
		for (j = 0; j < MARRIAGE; j++) {
			if (yznlife.wife[j].name == NULL ||yznlife.big_year[i] < yznlife.wife[j].love_years[0] || yznlife.big_year[i] > yznlife.wife[j].love_years[1]) {
				break;
			}
			yznlife.wife[j].wife_big[yznlife.wife[j].year++] = yznlife.big_year[i];
		}
	}

	for (j = 0; j < MARRIAGE; j++) {
		if (!yznlife.wife[j].name) {
			break;
		}
		printf("with wife %s, big year is ", yznlife.wife[j].name);
		for (i = 0; i < yznlife.wife[j].year; i++) {
			printf("%d, ", yznlife.wife[j].wife_big[i]);
		}
		printf("\n");
	}
	printf("-------------------------------------\n");
}

static void query_who_every_bigyear2(struct physicalst *yznlife)
{
	int i = 0, j = 0;

	for (i = 0; yznlife->big_year[i] != -0xff; i++) {
		for (j = 0; j < MARRIAGE; j++) {
			if (yznlife->wife[j].name == NULL || yznlife->big_year[i] < yznlife->wife[j].love_years[0] || yznlife->big_year[i] > yznlife->wife[j].love_years[1]) {
				break;
			}
			yznlife->wife[j].wife_big[yznlife->wife[j].year++] = yznlife->big_year[i];
		}
	}

	for (j = 0; j < MARRIAGE; j++) {
		if (!yznlife->wife[j].name) {
			break;
		}
		printf("with wife %s, big year is ", yznlife->wife[j].name);
		for (i = 0; i < yznlife->wife[j].year; i++) {
			printf("%d, ", yznlife->wife[j].wife_big[i]);
		}
		printf("\n");
	}
	printf("-------------------------------------\n");
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

//2.0 结构体名当做参数，并不会想指针一样传递指针，而是将整个结构体赋值一份给参数列表(这就包含了里面的数组成员等等都需要copy一份), 所以使用结构体指针会起到优化的作用。
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

		struct yangst *pyzn = &yznlife;
		print_yang_point(pyzn);
	}
//3.0 编写实现：如果Mils and yang parttime is {1956, 1957, 1958}, 请分析这个合作阶段有没有重大的发现，就是big_year !
	{
		struct yangst yznlife = {
			.name = "Yangzhenning",
			.no   = 'A',
			.age  = 95,
			.wife = "Duzhili",
			.big_year = {1942, 1954, 1956, 1958, 1966, 1971, 2003, -0xff},
			.partners = {"Feiman", "Mils", "Lizhengdao", "Wengfan", NULL},
			.parttime = {{1956, 1957, 1958, -0xff}, {1963, 1964, -0xff}},
		};
		char *pter = "Mils";
		int  ptime[] = {1956, 1957, 1958};

		/*query big year*/
		struct yangst *pyzn = &yznlife;
		int plen = sizeof(ptime)/sizeof(ptime[0]);
		int ret = 0;
		/* 0:false, 1:true*/
		ret = query_big_year(pyzn, pter, ptime, plen);
		if (ret < 1) {
			fprintf(stderr, "not find\n");
			exit(-1);
		}
	}

//4.0 编程实现：查询yangzhenning的大事年big year是发生在和谁的婚姻过程中。
	{
		struct physicalst yznlife = {
			.wife[0] = {
				.name = "duzhili",
				.love_years = {1956, 2003},
				.year = 0,
			},
			.wife[1] = {
				.name = "wengfan",
				.love_years = {2003, 2017},
				.year = 0,
			},

			.big_year = {1942, 1954, 1956, 1958, 1966, 1971, 2003, 2015, -0xff},
		};

		query_who_every_bigyear(yznlife);
	}

//4.1 使用另一种初始化结构体数组的方式，指针方式重新完成4.0的功能.
	{
		struct physicalst yznlife = {
			.wife = {
				[0] = {
					.name = "duzhili",
					.love_years = {1956, 2003},
					.year = 0,
				},
				[1] = {
					.name = "wengfan",
					.love_years = {2003, 2017},
					.year = 0,
				},
			},

			.big_year = {1942, 1954, 1956, 1958, 1966, 1971, 2003, 2015, -0xff},
		};

		struct physicalst *pyzn = &yznlife;
		query_who_every_bigyear2(pyzn);

	}

//4.2 不使用一次性初始化方式，首先定义一个结构体，然后逐个赋值

//4.3 使用指针方式 完成4.2所说的功能.

	return 0;
}
