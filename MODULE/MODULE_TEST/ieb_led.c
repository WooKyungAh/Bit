#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/input.h>
#include <linux/platform_device.h>
#include <linux/miscdevice.h>
#include <linux/device.h>
#include <linux/delay.h>

#include <linux/fs.h>
#include <linux/poll.h>
#include <linux/types.h>
#include <linux/ioport.h>

#include <asm/io.h>
#include <asm/delay.h>
#include <asm/irq.h>

#include <mach/map.h>
#include <mach/gpio.h>

#include <asm/gpio.h>
#include <mach/regs-gpio.h>

#include <plat/gpio-cfg.h>

#define DEVICE_NAME "led"
#define DEVICE_MAJOR    230

// Device Address
#define LED     0x0A

#define ADDR_PIN_L_0(x)           EXYNOS4212_GPM0(x+1)
#define ADDR_PIN_L_1(x)           EXYNOS4212_GPM1(x)

#define ADDR_PIN_H_1(x)           EXYNOS4212_GPM1(x+1)

#define DATA_PIN_2(x)             EXYNOS4212_GPM2(x)
#define DATA_PIN_3(x)             EXYNOS4212_GPM3(x)
#define DATA_PIN_4(x)             EXYNOS4212_GPM4(x)
#define DATA_PIN_0(x)             EXYNOS4212_GPM0(x)

static int n = 0;
static int count = 0;
static struct timer_list timer_str;
static void init_add_timer(void);
void timer_function(unsigned long ptr);
// 핀 재정의
 void gpio_init(void){
	int i;

	//fpga data gpio init - gpm2_0~2
        for(i=0; i<3; i++){
                gpio_request(DATA_PIN_2(i), "GPM2_0");
                s3c_gpio_cfgpin(DATA_PIN_2(i), S3C_GPIO_SFN(1));
                gpio_direction_output(DATA_PIN_2(i), 1);
        }
        //fpga data gpio init - gpm0_0
	for(i=0; i<1; i++){
                gpio_request(DATA_PIN_0(i), "GPM0_0");
                s3c_gpio_cfgpin(DATA_PIN_0(i), S3C_GPIO_SFN(1));
                gpio_direction_output(DATA_PIN_0(i), 1);
        }
        //fpga data gpio init - gpm2_3~4
        for(i=3; i<5; i++){
                gpio_request(DATA_PIN_2(i), "GPM2_0");
                s3c_gpio_cfgpin(DATA_PIN_2(i), S3C_GPIO_SFN(1));
                gpio_direction_output(DATA_PIN_2(i), 1);
        }
        //fpga data gpio init - gpm3_0~7
        for(i=0; i<2; i++){
                gpio_request(DATA_PIN_3(i), "GPM3_0");
                s3c_gpio_cfgpin(DATA_PIN_3(i), S3C_GPIO_SFN(1));
                gpio_direction_output(DATA_PIN_3(i), 1);
        }
        //fpga address gpio init - gpm0_1~7 <= (0~6+1) //add 1
        for(i=0; i<7; i++){
                gpio_request(ADDR_PIN_L_0(i), "GPM0_0");
                s3c_gpio_cfgpin(ADDR_PIN_L_0(i), S3C_GPIO_SFN(1));
                gpio_direction_output(ADDR_PIN_L_0(i), 0);
                gpio_set_value(ADDR_PIN_L_0(i), 0);
        }
        //fpga address gpio init - gpm1_0~0
        for(i=0; i<1; i++){
                gpio_request(ADDR_PIN_L_1(i), "GPM0_0");
                s3c_gpio_cfgpin(ADDR_PIN_L_1(i), S3C_GPIO_SFN(1));
                gpio_direction_output(ADDR_PIN_L_1(i), 0);
                gpio_set_value(ADDR_PIN_L_1(i), 0);
        }
        //fpga address gpio init - gpm1_1~6
        for(i=0; i<6; i++){
                gpio_request(ADDR_PIN_H_1(i), "GPM1_0");
                s3c_gpio_cfgpin(ADDR_PIN_H_1(i), S3C_GPIO_SFN(1));
                gpio_direction_output(ADDR_PIN_H_1(i), 0);
                gpio_set_value(ADDR_PIN_H_1(i), 0);
        }
}
// 출력핀 맵핑
void LED_DATA(unsigned char val)
{
 	if(val & (1<<0))    gpio_set_value(DATA_PIN_2(0), 1);
		else                gpio_set_value(DATA_PIN_2(0), 0);
	if(val & (1<<1))    gpio_set_value(DATA_PIN_2(1), 1);
		else                gpio_set_value(DATA_PIN_2(1), 0);
	if(val & (1<<2))    gpio_set_value(DATA_PIN_2(2), 1);
		else                gpio_set_value(DATA_PIN_2(2), 0);

	if(val & (1<<3))    gpio_set_value(DATA_PIN_0(0), 1);
		else                gpio_set_value(DATA_PIN_0(0), 0);

	if(val & (1<<4))    gpio_set_value(DATA_PIN_2(3), 1);
		else                gpio_set_value(DATA_PIN_2(3), 0);
	if(val & (1<<5))    gpio_set_value(DATA_PIN_2(4), 1);
		else                gpio_set_value(DATA_PIN_2(4), 0);

	if(val & (1<<6))    gpio_set_value(DATA_PIN_3(0), 1);
		else                gpio_set_value(DATA_PIN_3(0), 0);
	if(val & (1<<7))    gpio_set_value(DATA_PIN_3(1), 1);
		else                gpio_set_value(DATA_PIN_3(1), 0);

}
// write할때 어떤 출력단에 출력할지 선택 ... => LED로 출력한다고 알려줌
static void write_addr_l(unsigned char val){
	int i;

        for(i=0; i<7; i++){
                if(val & (1<<i)){
                        gpio_set_value(ADDR_PIN_L_0(i), 1);
                }
                else{
                        gpio_set_value(ADDR_PIN_L_0(i), 0);
                }
        }
        if(val & (1 << 7))
                gpio_set_value(ADDR_PIN_L_1(0), 1);
        else
                gpio_set_value(ADDR_PIN_L_1(0), 0);

}
// timer_str 구조체 설정 
void init_add_timer()
{
	init_timer(&timer_str);

	timer_str.function = &timer_function;
	timer_str.data = (unsigned long)n;
	timer_str.expires = jiffies + (HZ/1000);

	add_timer(&timer_str);
}
// 모듈종료시 timer 종료! 이거 없으면 rmmod하는순간 안드로이드 멈춰요..
void remove_timer(void)
{
	del_timer(&timer_str);
}

void Woo(void)
{
	unsigned char data;

	// 한바퀴 돌면 처음으로!
	if(count >= 14)
		count = 0;

	// LED를 오른쪽으로 하나씩 shift
	if(count < 8)
	{
		write_addr_l(LED);
		data = ~(0x01 << count);
		mod_timer(&timer_str, jiffies+HZ);
		LED_DATA(data);
		count++;
	}	// LED를 다시 왼쪽으로 shift
	else if(count > 7 && count < 14)
	{
		int cnt = count - 7;
		write_addr_l(LED);
		data = ~(0x80 >> cnt);
		mod_timer(&timer_str, jiffies+HZ);
		LED_DATA(data);
		count++;
	}
}

// 1초에 LED가 하나씩 shift되서 켜짐
void timer_function(unsigned long ptr)
{
	Woo();
	mod_timer(&timer_str, jiffies+HZ);
}

static int led_ioctl(struct inode *inode, struct file *file, unsigned int  cmd, unsigned long arg)
{
	return 0;
}

static int led_open(struct inode *minode, struct file *mfile)
{
	gpio_init();

	return 0;
}

static int led_release(struct inode *minode, struct file *mfile)
{
	gpio_init();
	return 0;
}

static ssize_t led_write (struct file *file, const char *buf, size_t count, loff_t *f_pos)
{
	char data[4];

	write_addr_l(LED);

	memset(data, 0, 1);
	copy_from_user(data, buf, count);

	LED_DATA(data[0]);

	return 0;
}

static struct file_operations led_fops = {
   .write      =   led_write,
   .open       =   led_open,
   .release    =   led_release,
   .unlocked_ioctl      =   led_ioctl,
};

static int __init led_init(void){
	int result;
	struct class *led_class;
        struct device *dev;

	result = register_chrdev(DEVICE_MAJOR, DEVICE_NAME, &led_fops);
	if (result < 0) {
		printk("unable to register device %s\n", DEVICE_NAME);
		return result;
	}
	printk("H-Smart4412TKU IEB: register device %s\n", DEVICE_NAME);
	
	led_class = class_create(THIS_MODULE, DEVICE_NAME);

        dev = device_create(led_class, NULL, MKDEV(DEVICE_MAJOR,0), NULL, DEVICE_NAME);
	
	gpio_init();
	init_add_timer();

	return 0;        

}

static void __exit led_exit(void){
	unregister_chrdev(DEVICE_MAJOR, DEVICE_NAME);
	remove_timer();
	gpio_init();
}

MODULE_LICENSE("GPL");
module_init(led_init);
module_exit(led_exit);
