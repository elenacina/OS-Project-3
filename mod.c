#include <linux/blkdev.h>
#include <linux/bio.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/sched/task.h>
#include <linux/sched/signal.h>
#include <linux/sched.h> 
#include <linux/pid.h>
#include <linux/fdtable.h>
#include <linux/fs.h>
#include <linux/path.h>
#include <linux/dcache.h>
#include <linux/namei.h>
#include <linux/proc_fs.h>
#include <linux/mm.h>
#define PAGESIZE 4096
#define NUM_ENTRIES 512
#define PG_AD 549755813888   //2^39

int processid;
module_param(processid,int,000);

void memInfo(void)
{
	bool found = false;
	struct task_struct *task = current;
	struct task_struct *t;
	struct vm_area_struct *v;
	struct mm_struct *m; 
	unsigned long t_size = 0;
	
	rcu_read_lock();
	for_each_process(task)
	{
		task_lock(task);
		int iid = task -> pid;
		if(iid == processid)
		{	
			t = task;
			found = true;
		}
		task_unlock(task);
				
	}
	rcu_read_unlock();
	
	if(found)
	{
		printk("===== VIRTUAL MEMORY INFORMATION ===== \n\n");
		v = t -> mm -> mmap;
		if(v != NULL)
		{
				printk("Process: [%d]\n", t -> pid);
			while(v -> vm_next != NULL)
			{
				unsigned long size = v -> vm_end - v -> vm_start;
				t_size = t_size + size;
				printk("Start: 0x%lx, End: 0x%lx, Region Size: 0x%lx\n", v -> vm_start, v -> vm_end, size);
				v = v -> vm_next;
			}
			printk("Total size of virtual space is: 0x%lx\n",t_size);
			printk("\n");

		}
		
		printk("===== HEAP INFORMATION ===== \n\n");
		m = t -> mm ;
		printk("Start address of heap: 0x%lx\n", m-> start_brk);
		printk("End address of heap: 0x%lx\n", m-> brk);
		
		//unsigned long s_heap = m-> brk - m-> start_brk;
		
		printk("The size of the heap is 0x%d\n" , m-> brk - m-> start_brk);
		
		printk("\n"); 
				
		printk("===== ENVIROMENT INFORMATION ===== \n\n");
		
		printk("Start address of the enviroment variables: 0x%lx\n", m-> env_start);
		printk("End address of the enviroment variables: 0x%lx\n", m-> env_end);
		
		//unsigned long s_env = m-> env_end - m-> env_start;
		
		printk("The size of the enviroment variables is 0x%lx\n" ,  m-> env_end - m-> env_start);
		
		printk("\n");
		
		printk("===== CODE INFORMATION ===== \n\n");
		
		
		printk("Start address of code: 0x%lx\n", m-> start_code);
		printk("End address of code: 0x%lx\n", m-> end_code);
		
		//unsigned long s_code = m-> end_code - m-> start_code;
		
		printk("The size of the code is 0x%lx\n" , m-> end_code - m-> start_code);
		
		printk("\n");
		
		printk("===== DATA INFORMATION =====\n\n");
		
		
		printk("Start address of data: 0x%lx\n", m-> start_data);
		printk("End address of data: 0x%lx\n", m-> end_data);
		
		//unsigned long s_data = m-> end_data - m-> start_data;
		
		printk("The size of the data is 0x%lx\n" , m-> end_data - m-> start_data);
		
		printk("\n");
		
		printk("===== ARGUMENTS INFORMATION ===== \n\n");
		
		
		printk("Start address of arguments: 0x%lx\n", m-> arg_start);
		printk("End address of arguments: 0x%lx\n", m-> arg_end);
