#include <linux/module.h>
#include <linux/kernel.h>

int var = 20;

int init_module(void)
{
	printk("\nVariabile value: %d \n\n", var);
	return 0;
}

void cleanup_module(void)
{
	printk("\nBye bye \n\n");
}