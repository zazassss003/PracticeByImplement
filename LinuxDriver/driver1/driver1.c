/*
This code initialize the char driver, we can input 1 and 0 to controll LED on and off and see the message from kernel to 
check the current state, however this code does not directly contact with hardware so it can't actually turn on the LED.
So the next thing we do is to add the GPIO in the write function.
*/


#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>


#define DRIVER_NAME  "drvled"


#define LED_OFF        0
#define LED_ON         1


static struct {
	dev_t devnum;
	struct cdev cdev;
	unsigned int led_status;
} drvled_data;


static void drvled_setled(unsigned int status)
{
	drvled_data.led_status = status;
}


static ssize_t drvled_read(struct file *file, char __user *buf,
			   size_t count, loff_t *ppos) // Read function to check the current state
{
	static const char * const msg[] = { "OFF\n", "ON\n" };
	int size;


	/* check if EOF */
	if (*ppos > 0)
		return 0;


	size = strlen(msg[drvled_data.led_status]);
	if (size > count)
		size = count;


	if (copy_to_user(buf, msg[drvled_data.led_status], size))
		return -EFAULT;


	*ppos += size;


	return size;
}


static ssize_t drvled_write(struct file *file, const char __user *buf,
			    size_t count, loff_t *ppos)
{
	char kbuf = 0;


	if (copy_from_user(&kbuf, buf, 1))
		return -EFAULT;


	if (kbuf == '1') {
		drvled_setled(LED_ON);
		pr_info("LED ON!\n");
	} else if (kbuf == '0') {
		drvled_setled(LED_OFF);
		pr_info("LED OFF!\n");
	}


	return count;
}


static const struct file_operations drvled_fops = {
	.owner = THIS_MODULE,
	.write = drvled_write,
	.read = drvled_read,
};


static int __init drvled_init(void)
{
	int result;


	result = alloc_chrdev_region(&drvled_data.devnum, 0, 1, DRIVER_NAME);
	if (result) {
		pr_err("%s: Failed to allocate device number!\n", DRIVER_NAME);
		return result;
	}


	cdev_init(&drvled_data.cdev, &drvled_fops);


	result = cdev_add(&drvled_data.cdev, drvled_data.devnum, 1);
	if (result) {
		pr_err("%s: Char device registration failed!\n", DRIVER_NAME);
		unregister_chrdev_region(drvled_data.devnum, 1);
		return result;
	}


	drvled_setled(LED_OFF);


	pr_info("%s: initialized.\n", DRIVER_NAME);
	return 0;
}


static void __exit drvled_exit(void)
{
	cdev_del(&drvled_data.cdev);
	unregister_chrdev_region(drvled_data.devnum, 1);
	pr_info("%s: exiting.\n", DRIVER_NAME);
}


module_init(drvled_init);
module_exit(drvled_exit);


MODULE_LICENSE("GPL");
MODULE_VERSION("1.0");

