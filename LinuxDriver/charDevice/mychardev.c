#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/cdev.h>


#define DRIVER_NAME "cdriver"
#define BUFFER_SIZE 128

static char device_buffer[BUFFER_SIZE]; /* maintain a buffer in drvier */
static int buffer_size = 0; /* current buffer size */


static struct{
	dev_t deviceNum;
	struct cdev cdev;
} cdriver_data;


static int cdriver_open(struct inode *inode, struct file *file)
{
	pr_info("%s: Device opened!\n", DRIVER_NAME);
	return 0;
}


static ssize_t cdriver_read(struct file *file, const char __user *buf, size_t count, loff_t *pos)
{
	if(*pos > buffer_size) return 0;
	if(count > buffer_size - *pos) count = buffer_size - *pos;
	if(copy_to_user(buf, device_buffer + *pos, count)) return -EFAULT;
	*pos += count;

	return count;
}
static ssize_t cdriver_write(struct file *file, const char __user *buf, size_t count, loff_t *pos)
{
	if(count > BUFFER_SIZE) count = BUFFER_SIZE;
	if(copy_from_user(device_buffer, buf, count)) return -EFAULT;
	buffer_size = count;

	pr_info("%s: written %zu bytes.", DRIVER_NAME, count);

	return count;
}

static int cdriver_close(struct inode *inode, struct file *file)
{
	pr_info("%s: Device closed!\n", DRIVER_NAME);
	return 0;
}

static long cdriver_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	switch (cmd) {
		case IOCTL_CLEAR_BUFFER:
			memset(device_buffer, 0, BUFFER_SIZE);
			buffer_size = 0;
			pr_info("%s: Buffer cleared.\n", DRIVER_NAME);
			break;
		case IOCTL_GET_BUFFER_SIZE:
			if(copy_to_user((int __user *) arg, &buffer_size, sizeof(buffer_size))) 
				return -EFAULT;
			pr_info("%s: Buffer size: %d bytes\n", DRIVER_NAME, buffer_size);
			break;
		default:
			return -EINVAL;

	}

	return 0;
}

static const struct file_operations cdriver_fops = {
        .owner = THIS_MODULE,
        .write = cdriver_write,
        .read  = cdriver_read,
        .open  = cdriver_open,
		.release = cdriver_close,
		.unlock_ioctl = cdriver_ioctl,
};



static int __init cdriver_init(void)
{
	int result;

	result = alloc_chrdev_region(&cdriver_data.deviceNum, 0, 1, DRIVER_NAME);
	if (result){
		pr_err("%s: Fail to allocate device number!\n", DRIVER_NAME);
		return result;
	}
	
	cdev_init(&cdriver_data.cdev, &cdriver_fops);
	result = cdev_add(&cdriver_data.cdev, cdriver_data.deviceNum, 1);
	if (result) {
		pr_err("%s: Char device registeration failed!\n", DRIVER_NAME);
		unregister_chrdev_region(cdriver_data.deviceNum, 1);
		return result;
	}
	
	pr_info("%s: initialized.\n", DRIVER_NAME);
	return 0;
	

}


static void cdriver_exit(void)
{
	cdev_del(&cdriver_data.cdev);
	unregister_chrdev_region(cdriver_data.deviceNum, 1);
	pr_info("%s: exiting.\n", DRIVER_NAME);

}

module_init(cdriver_init);
module_exit(cdriver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("VicentK");
MODULE_DESCRIPTION("Simple Linux Character Device Driver");
MODULE_VERSION("1.0");


