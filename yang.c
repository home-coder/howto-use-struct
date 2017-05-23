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

struct physicalst2 {
	struct his_wife *wife;
	int big_year[20];
};

struct physicalst3 {
	struct his_wife **wife;
	int big_year[20];
};

typedef enum {false = 0, true}bool;

struct contribution {
	int year;
	char *invention;
};

struct partner {
	char *partname;
	int parttime[3][2]; //假设最多合作过3段时间，每段区间如 {1956, 1962}
};

struct physicalst5 {
	char *name;
	struct contribution cbution[5]; //最多五个贡献
	struct partner pners[3]; //最多三个合作者
	void (*query_invention_partname)(struct physicalst5 *, char *, int *); //yangzhenning, {1956, 1962}
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

static void print_everywife_name(struct physicalst2 yznlife)
{
	int i = 0;

	for (i = 0; i < MARRIAGE; i++) {
		if (!(yznlife.wife + i)->name) {
			break;
		}
		printf("his %d wife name is %s \n", i + 1, (yznlife.wife + i)->name);
	}
	printf("-------------------------------------\n");
}

static void print_everywife_name2(struct physicalst3 *yznlife)
{
	int i = 0;

	for (; *(yznlife->wife) != NULL; yznlife->wife++) {
		printf("his %d wife name is %s\n", i++, (*yznlife->wife)->name); //优先级问题,箭头   -> 和 []   是一个级别的属于一等优先
	}
	printf("-------------------------------------\n");
}

static void inner_querypp(struct physicalst5 *phylife, char *name, int *region)
{
	struct physicalst5 *pplife = phylife;
	int from = region[0], end = region[1];

	for (; pplife != NULL; pplife++) {
		if (!strcmp(pplife->name, name)) {
			struct contribution *pcb = pplife->cbution;	
			for (; pcb->year != -0xff; pcb++) {
				if ( (pcb->year >= from) && (pcb->year <= end) ) {
					printf("debug: year(%d)--%d\n", pcb->year, __LINE__);
					struct partner *ppt = pplife->pners;
					for (; ppt->partname != NULL; ppt++) {
						printf("partname %s\n", ppt->partname);	
						int *ptime = ppt->parttime[0];
					}
				}
			}
		}
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
//3.1 使用逐个初始化的方式，并且使用指针形式，重新实现3.0的功能，注意此功能有些复杂，需要完全抛弃原来的观念，重新实现.

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
	{
		struct physicalst yznlife = {
			.big_year = {1942, 1954, 1956, 1958, 1966, 1971, 2003, 2015, -0xff},
		};
		yznlife.wife[0].name = "duzhili";
		yznlife.wife[0].year = 0;

		yznlife.wife[0].love_years[0] = 1956;
		yznlife.wife[0].love_years[1] = 2003;

		yznlife.wife[1].name = "wengfan";
		yznlife.wife[1].year = 0;

		yznlife.wife[1].love_years[0] = 2003;
		yznlife.wife[1].love_years[1] = 2017;

		query_who_every_bigyear(yznlife);
	}
//4.2.1 但独将 his_wife作为一个结构体初始化，然后通过指针指向这个结构体
	{
		struct his_wife thiswife[MARRIAGE] = {
			[0] = {
				.name = "duzhili",
				.year = 0,
			},
			[1] = {
				.name = "wengfan",
				.year = 0,
			},
		};

		struct physicalst2 yznlife = {
			.wife = thiswife,
			.big_year = {1942, 1954, 1956, 1958, 1966, 1971, 2003, 2015, -0xff},
		};

		print_everywife_name(yznlife);
		//query_who_every_bigyear3(yznlife);
	}
//4.2.2 自己总结性文章一个，  放到README.md当中，取名《结构体成员初始化的归纳》

//4.3 使用指针方式 完成4.2所说的功能. 当然还有一个联系的目的是，数组的赋值问题，初始化倒是好办（定义的时候直接赋予一个初始值）， 但是单纯的赋值就有讲究了，必须按照C语言的标准来，按照最小元素赋值.
	{
		struct his_wife *thiswife[MARRIAGE];
		int i;

		for (i = 0; i < MARRIAGE-1; i++) {
			thiswife[i] = (struct his_wife *)malloc(sizeof(struct his_wife));
			if (!thiswife[i]) {
				fprintf(stderr, "malloc error\n");
				exit(-1);
			}
		}
		thiswife[MARRIAGE-1] = NULL;

		thiswife[0]->name = "duzhili";
		thiswife[0]->year = 0;
		thiswife[1]->name = "wengfan";
		thiswife[1]->year = 0;

		struct physicalst3 *yznlife = (struct physicalst3 *)malloc(sizeof(*yznlife));
		/*注意所有遍历数组都是先存好第一个元素的地址，结构体也不例外, 当然也可以使用int i来遍历*/
		yznlife->wife = thiswife;

		print_everywife_name2(yznlife);
	}

//4.4 使用physicalst3的二级指针, 其中的元素直接指向一个初始化好的结构体，并完成4.3的相同工作
	{
		struct his_wife thiswife[MARRIAGE] = {
			[0] = {
				.name = "duzhili",
			},
			[1] = {
				.name = "wengfan",
			},
		};

		struct physicalst3 *yznlife = (struct physicalst3 *)malloc(sizeof(*yznlife));
		yznlife->wife = (struct his_wife **)malloc(sizeof(struct his_wife *) * MARRIAGE);

		yznlife->wife[0] = &thiswife[0];
		yznlife->wife[1] = &thiswife[1];

		print_everywife_name2(yznlife);
	}

//5.0 设计结构体，yangzhenning, mils, newton, feiman, albert . 随便输入一个时间段(1906, 1933),输出这个期间的获取诺贝尔的物理家的成果和合作者，不要考虑时间重合多个合作者，那是下一步的事情
      //不要把结构体设计成成果和你年限放到一体，比如{"yangzhenning", {1953, 2003}, "yang-mils function", "yang-lizhegdao function"}
	  //使用链表或者什么将所有物理家的共性连到一起,下一步的事情

	{
		struct physicalst5 phylife[5] = {
			[0] = {
				.name = "yangzhenning",
				.cbution = {
					[0] = {
						.year = 1952,
						.invention = "Yang 1st NB",
					},
					[1] = {
						.year = 1954,
						.invention = "Yang 2st NB",
					},
					[2] = {
						.year = 1956,
						.invention = "Yang 3st HenNB",
					},
					[3] = {
						.year = 1962,
						.invention = "Yang 4st Old NB",
					},
					[4] = -0xff,
				},
				.pners = {
					[0] = {
						.partname = "Lizhengdao",
						.parttime = {{1952, 1953}, {1955, 1958}},
					},
					[1] = {
						.partname = "mils",
						.parttime = {{1960, 1967}, {1977, 1983}},
					},
					[2] = NULL,
				},

				.query_invention_partname = inner_querypp,
			},

			[1] = NULL,
		};
		char *p = 0;
		int region[] = {1957, 1958};
		inner_querypp(phylife, "yangzhenning", region);
	}

//5.1 结构体数组的初始化问题,比如数组第一个元素代表什么的问题。
	{
		struct phytest {
			int a;
			char *b;
		};

		struct phytest ptest[] = {
			[0] = {
				.a = 1,
				.b = "phy test",
			},
			[1] = -0xff,
		};

		printf("-----编译通过-----\n");

		struct phytest2 {
			char *b;
			int a;
		};

		struct phytest2 ptest2[] = {
			[0] = {
				.a = 1,
				.b = "phy test2"
			},
			[1] = {NULL},
		};
		printf("-----编译通过-----\n");
	}
//5.2 结构体默认初始值问题,如果以5.1的test2为例就要判断是否为空。
	{
		struct phytest2 {
			char *b;
			int a;
		};

		struct phytest2 ptest2[] = {
			[0] = {
				.a = 1,
				.b = "no null",
			},
			[1] = NULL,
		};

		struct phytest2 *ppt = ptest2;
		for (; ppt->b != NULL; ppt++) {
			printf("%s\n", ppt->b);
		}
	}
//6.0 思考使用宏函数来实现上面繁琐的赋值过程
	return 0;
}
