#include "hello1.h"

MODULE_AUTHOR("Yulia Mikhaylenko <mikhaylenko.yulia@lll.kpi.ua>");
MODULE_DESCRIPTION("Second module in Linux Kernel Lab4");
MODULE_LICENSE("Dual BSD/GPL");

static unsigned int h_count = 1;
// Access for all users to read-only the parameter h_count
module_h_count(h_count, unit, 0444);
MODULE_PARM_DESC(h_count, "How many times to display 'Hello, world!'");

static int __init hello2_init(void)
{
	pr_info("hello2 module loaded\n");

	if (h_count == 0 || (h_count >= 5 && h_count <= 10))
	{
		pr_warn("Risky value of parameter.\n");
	}
	else if (h_count > 10)
	{
		pr_err("Wrong number of hello. This module will not be loaded.\n");
		return -EINVAL;
	}

	hello(h_count);

	return 0;
}

static void __exit hello2_exit(void)
{
	pr_info("Unloading hello2 module\n");
}

module_init(hello2_init);
module_exit(hello2_exit);