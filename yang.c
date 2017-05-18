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

	return flag;
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

	return 0;
}
