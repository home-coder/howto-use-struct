#define LRADC_BASE_ADDR         (0xf1c22800)
#define REG_ADDR(offset)        (volatile void __iomem *)(LRADC_BASE_ADDR + offset)

#define LRADC_CTRL              REG_ADDR(0x00)
#define LRADC_INTC              REG_ADDR(0x04)
#define LRADC_INTS              REG_ADDR(0x08)
#define LRADC_DATA0             REG_ADDR(0x0c)

struct sunxi_adc_reg_addr{
	volatile void __iomem *ctrl;
	volatile void __iomem *intc;
	volatile void __iomem *ints;
	volatile void __iomem *data0;
};

static struct sunxi_adc_reg_addr sunxi_adc_reg = {
	LRADC_CTRL,
	LRADC_INTC,
	LRADC_INTS,
	LRADC_DATA0,
};

static struct keyadc_dev{  
	dev_t devid;  
	struct cdev chrdev;  
	struct class *class;  
	struct input_dev *input;  

	struct workqueue_struct *keyadc_workqueue;  
	struct work_struct keyadc_work;  

	unsigned int keycode;  
	struct sunxi_adc_reg_addr *regs;
};    

static struct keyadc_dev keyadc_pdata = {  
	.regs = &sunxi_adc_reg,
};  

static struct platform_device keyadc_device = {  
	.name   = PLATFORMNAME,  
	.id = -1,  
	.dev    = {  
		.platform_data = &keyadc_pdata,  
	}         
};  
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct MyStruct
{
	int a;
	int b;
	char* c;
};

int main()
{
	struct MyStruct t1;
	t1.a = 1;
	t1.b = 2;
	// 为指针区域赋值
	char *p = (char*)malloc(10*sizeof(char));
	strcpy(p, "hello");
	t1.c = p;

	struct MyStruct t2;
	t2 = t1;
	printf("MyStruct t1: %d, %d, %s\n", t1.a, t1.b, t1.c);
	// 释放了t1的内存
	//free(p);
	printf("MyStruct t2: %d, %d, %s\n", t2.a, t2.b, t2.c);


	printf("t1 pointer addr: %p\n", t1.c);
	printf("t2 pointer addr: %p\n", t2.c);

	return 0;
}
