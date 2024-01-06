#include <linux/slab.h>
#include "hello1.h"

MODULE_AUTHOR("Yulia Mikhaylenko <mikhaylenko.yulia@lll.kpi.ua>");
MODULE_DESCRIPTION("hello() function for Lab4");
MODULE_LICENSE("Dual BSD/GPL");

static LIST_HEAD(event_list);

void hello(unsigned int h_count)
{
	int i;
	for (i = 0; i < h_count; i++)
	{
		struct event_data *event = kmalloc(sizeof(*event), GFP_KERNEL);
		event->timestamp = ktime_get();
		list_add(&event->list, &event_list);
		pr_info("Hello, world!\n");
		event->print_duration = ktime_sub(ktime_get(), event->timestamp);
	}
}

EXPORT_SYMBOL(hello);

static int __init hello1_init(void)
{
	pr_info("hello1 module loaded\n");
	return 0;
}

static void __exit hello1_exit(void)
{
	struct event_data *event, *temp;

	list_for_each_entry_safe(event, temp, &event_list, list)
	{
		ktime_t duration = ktime_sub(ktime_get(), event->timestamp);
		pr_info(
			"Event time: %lld, Print time: %lld\n",
			ktime_to_ns(duration),
			ktime_to_ns(event->print_duration)
		);
		list_del(&event->list);
		kfree(event);
	}

	pr_info("Unloading hello1 module\n");
}

module_init(hello1_init);
module_exit(hello1_exit);