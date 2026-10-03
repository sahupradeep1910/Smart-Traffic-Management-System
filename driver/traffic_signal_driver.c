#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/string.h>

#define DEVICE_NAME "traffic_signal"

static dev_t dev_number;
static struct cdev traffic_cdev;
static struct class *traffic_class;

static char signal_state[16] = "RED";
static int traffic_open(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "traffic_signal: device opened\n");
    return 0;
}

static int traffic_release(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "traffic_signal: device closed\n");
    return 0;
}
static ssize_t traffic_read(struct file *file, char __user *buffer,
                            size_t length, loff_t *offset)
{
    return simple_read_from_buffer(buffer, length, offset,
                                   signal_state, strlen(signal_state));
}

static ssize_t traffic_write(struct file *file,
                             const char __user *buffer,
                             size_t length, loff_t *offset)
{
    char input[16];

    if (length >= sizeof(input))
        return -EINVAL;

    if (copy_from_user(input, buffer, length))
        return -EFAULT;

    input[length] = '\0';

    if (input[length - 1] == '\n')
        input[length - 1] = '\0';

    if (strcmp(input, "RED") == 0 ||
        strcmp(input, "GREEN") == 0 ||
        strcmp(input, "YELLOW") == 0)
    {
        strscpy(signal_state, input, sizeof(signal_state));
        printk(KERN_INFO "traffic_signal: signal changed to %s\n",
               signal_state);
        return length;
    }

    printk(KERN_WARNING "traffic_signal: invalid signal state\n");
    return -EINVAL;
}
static struct file_operations traffic_fops = {
    .owner = THIS_MODULE,
    .open = traffic_open,
    .read = traffic_read,
    .write = traffic_write,
    .release = traffic_release,
};
static int __init traffic_driver_init(void)
{
    alloc_chrdev_region(&dev_number, 0, 1, DEVICE_NAME);

    cdev_init(&traffic_cdev, &traffic_fops);
    cdev_add(&traffic_cdev, dev_number, 1);

    traffic_class = class_create(DEVICE_NAME);

    device_create(traffic_class, NULL, dev_number, NULL, DEVICE_NAME);

    printk(KERN_INFO "traffic_signal: driver loaded\n");

    return 0;
}
static void __exit traffic_driver_exit(void)
{
    device_destroy(traffic_class, dev_number);
    class_destroy(traffic_class);
    cdev_del(&traffic_cdev);
    unregister_chrdev_region(dev_number, 1);

    printk(KERN_INFO "traffic_signal: driver unloaded\n");
}
module_init(traffic_driver_init);
module_exit(traffic_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Smart Traffic Management System");
MODULE_DESCRIPTION("Traffic Signal Character Device Driver");
