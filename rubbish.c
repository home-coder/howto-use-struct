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
