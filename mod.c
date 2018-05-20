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
		
			//unsigned long s_arg = m-> arg_end - m-> arg_start;
		
		printk("The size of the arguments is 0x%lx\n" , m-> arg_end - m-> arg_start);
		
		printk("\n");
		
		
		printk("===== STACK INFORMATION ===== \n\n");
		
		//printk("Start address of stack: 0x%lx\n", m-> start_stack);
		m = t -> mm ;
		unsigned long startS = m-> start_stack;
		unsigned long S_size = 0;
		v =  t -> mm -> mmap;

		
		while(v -> vm_next != NULL){
		
		if(likely(v->vm_flags & VM_STACK)){
		
		printk("THE Start address of the stack is: 0x%lx\n", v -> vm_start);
		unsigned long size = v -> vm_end - v -> vm_start;	
		
		printk("The end address of the stack is 0x%lx\n" , v -> vm_end);			
		
		S_size = S_size + size;
		
		}
		v = v -> vm_next;
		}
		
		
		printk("The size of Stack is 0x%lx\n" , S_size);
		
		printk("\n");
		
		
		printk("===== NUMBER OF FRAMES INFORMATION ===== \n\n");
		
		unsigned long frames = get_mm_rss(m);
		printk("The number of frames is: 0x%lx\n" , frames);
		
		printk("\n");
		
		printk("===== OUTER PAGE INFORMATION =====\n\n");
		
		pgd_t *pgd;
		
		v =  t -> mm -> mmap;
		//printk("The VM Starting address is  0x%lx\n",v -> vm_start);
		
		//converting 
		pgd = pgd_offset(m,v -> vm_start);	
		unsigned long vm = v -> vm_start; 


		int i=0;
		while( i<512){
		
			
			if (!pgd_none(pgd[i]) || !pgd_bad(pgd[i])){
			     printk("[%d] -  0x%lx\n",i, pgd[i]); 
				int pd = pgd_val(pgd[i]);




				long long bit  = pd & 1;
				long long bit1 = (pd & 2)>> 1;
				long long bit2 = (pd & 4)>> 2;
				long long bit3 = (pd & 8)>> 3;
				long long bit4 = (pd & 16)>> 4;
				long long  bit5 = (pd & 32)>> 5;
				//int bit6 = (pd & 64)>> 6;
				long long bit7 = (pd & 128)>>7;
				long long pa = (pd & 4503599627366400) >>12;
				long long reserved = (pd & 4503599627370496) >>52 ;//0000000000001000000000000000000000000000000000000000000000000000
				long long xd = pd >>63;




				printk("| P    %10d |",bit  );
				printk("| R/W  %10d |",bit1 );
				printk("| U/S  %10d |",bit2 );
				printk("| PWT  %10d |",bit3 );
				printk("| PCD  %10d |",bit4 );
				printk("| A    %10d |",bit5 );
				printk("| PS   %10d |",bit7 );
				printk("| PA      0x%lx |",pa );
				printk("| Reserved %6d |", reserved);
				printk("| XD   %10d |", xd);
				
				
				printk ("===================");
			}
			     
			//  vm = vm + PG_AD;
			 
			 //pgd = pgd_offset(m,vm);
		
				 i++;
		}
		
		
	}
	else
	{
		printk("ID not found\n");
	}

}



int i_mod(void)
{
  
	struct task_struct *task;
	task = &init_task;
	printk("\n\n"); 
	memInfo();
	return 0;	
}

	
	
void e_mod(void)
{
	printk("Done\n");
}

module_init(i_mod);
module_exit(e_mod);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("[Kernel Module for Memory Management]");
MODULE_AUTHOR("Elena Cina & Eniselda Tusku");

