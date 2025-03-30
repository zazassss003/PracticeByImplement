#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/leds.h>
#include <linux/slab.h>
#include <linux/gpio.h>
#include <linux/gpio/consumer.h>
#include <linux/platform_device.h>
#include <linux/of_gpio.h>


#define LED_OFF	0
#define LED_ON	1


struct drvled_data_st {
	struct gpio_desc *desc;
	struct led_classdev led_cdev;
};


static struct drvled_data_st *drvled_data;


static void drvled_setled(unsigned int status)
{
	if (status == LED_ON)
		gpiod_set_value(drvled_data->desc, 1);
	else
		gpiod_set_value(drvled_data->desc, 0);
}


static void drvled_change_state(struct led_classdev *led_cdev,
				enum led_brightness brightness)
{
	if (brightness)
		drvled_setled(LED_ON);
	else
		drvled_setled(LED_OFF);
}


static int drvled_probe(struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	struct device_node *child = NULL;
	int result, gpio;


	child = of_get_next_child(np, NULL);


	drvled_data = devm_kzalloc(&pdev->dev, sizeof(*drvled_data),
				   GFP_KERNEL);
	if (!drvled_data)
		return -ENOMEM;


	gpio = of_get_gpio(child, 0);


	result = devm_gpio_request(&pdev->dev, gpio, pdev->name);
	if (result) {
		dev_err(&pdev->dev, "Error requesting GPIO\n");
		return result;
	}


	drvled_data->desc = gpio_to_desc(gpio);


	drvled_data->led_cdev.name = of_get_property(child, "label", NULL);
	drvled_data->led_cdev.brightness_set = drvled_change_state;


	result = devm_led_classdev_register(&pdev->dev, &drvled_data->led_cdev);
	if (result) {
		dev_err(&pdev->dev, "Error registering led\n");
		return result;
	}


	gpiod_direction_output(drvled_data->desc, 0);


	dev_info(&pdev->dev, "initialized.\n");


	return 0;
}


static int drvled_remove(struct platform_device *pdev)
{
	dev_info(&pdev->dev, "exiting.\n");


	return 0;
}


static const struct of_device_id of_drvled_match[] = {
	{ .compatible = "labworks,drvled" },
	{},
};


static struct platform_driver drvled_driver = {
	.driver = {
		.name	= "drvleds",
		.owner	= THIS_MODULE,
		.of_match_table = of_drvled_match,
	},
	.probe		= drvled_probe,
	.remove		= drvled_remove,
};


module_platform_driver(drvled_driver);


MODULE_LICENSE("GPL");
MODULE_VERSION("1.0");

