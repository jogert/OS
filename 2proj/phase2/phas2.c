/* Ian J & Derek M */

#include <linux/module.h>
#include <linux/syscalls.h>
#include <linux/types.h>
#include <linux/sched.h>
#include <linux/time.h>
#include <linux/list.h>

#include <asm/current.h>
#include <asm/uaccess.h>

/* Struct stored here */
#include "pinfo.h"


unsigned long **sys_call_table;

asmlinkage long (*ref_sys_cs3013_syscall2)(void);


asmlinkage long new_sys_cs3013_syscall2(struct processinfo* info) {
  
  /* Make kinfo and temp valuej structs */
    struct processinfo kinfo;
    struct task_struct* kid;
    struct task_struct* sib;
    struct task_struct* youngestKid;
    struct task_struct* youngerSib;
    struct task_struct* olderSib;
    
  /* Initialize temps calling them kids
   * or sibs for distinguishability */
    kid = NULL;
    sib = NULL;
    youngestKid = NULL;
    youngerSib = NULL;
    olderSib = NULL;

  /* Initialize kinfo struct */
    kinfo.state = current->state;
    kinfo.pid = current->pid;
    kinfo.parent_pid = current->parent->pid;
    kinfo.youngest_child = -1;
    kinfo.younger_sibling = -1;
    kinfo.older_sibling = -1;
    kinfo.uid = current_uid().val;
    kinfo.start_time = -1;
    kinfo.user_time = -1;
    kinfo.sys_time = -1;
    kinfo.cutime = 0;
    kinfo.cstime = 0;

    


  /* Update the times of the youngest kid */
    list_for_each_entry(kid, &(current->children), sibling){
        kinfo.cutime += cputime_to_usecs(kid->utime);
        kinfo.cstime += cputime_to_usecs(kid->stime);

      /* If kid is closer to present than youngestKid or still at it's initialized value */
        if ((youngestKid == NULL) || (timespec_compare(&kid->start_time, &youngestKid->start_time) > 0)){
                youngestKid = kid;
        }
    }

  /* Find younger & older for each sib */
    list_for_each_entry(sib, &(current->sibling), sibling){
      
      /* If sib is closer to present than start time & either youngerSib is 
       * at it's initialized value or older */
        if ((youngerSib == NULL || timespec_compare(&sib->start_time, &youngerSib->start_time) < 0)
            && (timespec_compare(&sib->start_time, &current->start_time) > 0)){
                youngerSib = sib;
        }
      /* If sib is further from present than start time & either youngerSib is 
       * at it's initialized value or younger */
        if ((olderSib == NULL || timespec_compare(&sib->start_time, &olderSib->start_time) > 0)
            && (timespec_compare(&sib->start_time, &current->start_time) < 0)){
                olderSib = sib;
        }
    }

  /* Put the kids and the time into kinfo */
    // if (youngestKid != NULL){
    //     kinfo.youngest_child = youngestKid->pid;
    // }
    // kinfo.youngest_child = -1;
    // if (youngerSib != NULL){
    //     kinfo.younger_sibling = youngerSib->pid;
    // }
    // kinfo.younger_sibling = -1;
    // if (youngestKid != NULL){
    //     kinfo.older_sibling = olderSib->pid;
    // }
    // kinfo.older_sibling = -1;
    kinfo.youngest_child = (youngestKid != NULL) ? youngestKid->pid : -1;
    kinfo.younger_sibling = (youngerSib != NULL) ? youngerSib->pid : -1;
    kinfo.older_sibling = (olderSib != NULL) ? olderSib->pid : -1;
    kinfo.start_time = timespec_to_ns(&current->start_time);
    kinfo.user_time = cputime_to_usecs(current->utime);
    kinfo.sys_time = cputime_to_usecs(current->stime);
  /* Copy struct */
    if (copy_to_user(info, &kinfo, sizeof kinfo)){
        return EFAULT;
    }
    return 0;
}


/* function to find the system call */
static unsigned long **find_sys_call_table(void) {
  unsigned long int offset = PAGE_OFFSET;
  unsigned long **sct;
  
  while (offset < ULLONG_MAX) {
    sct = (unsigned long **)offset;

    if (sct[__NR_close] == (unsigned long *) sys_close) {
      printk(KERN_INFO "Interceptor: Found syscall table at address: 0x%02lX",
                (unsigned long) sct);
      return sct;
    }
    
    offset += sizeof(void *);
  }
  
  return NULL;
}

/* lets processes alter read only files */
static void disable_page_protection(void) {
  /*
    Control Register 0 (cr0) governs how the CPU operates.

    Bit #16, if set, prevents the CPU from writing to memory marked as
    read only. Well, our system call table meets that description.
    But, we can simply turn off this bit in cr0 to allow us to make
    changes. We read in the current value of the register (32 or 64
    bits wide), and AND that with a value where all bits are 0 except
    the 16th bit (using a negation operation), causing the write_cr0
    value to have the 16th bit cleared (with all other bits staying
    the same. We will thus be able to write to the protected memory.

    It's good to be the kernel!
   */
  write_cr0 (read_cr0 () & (~ 0x10000));
}

/* prevents processes from altering read only files */
static void enable_page_protection(void) {
  /*
   See the above description for cr0. Here, we use an OR to set the 
   16th bit to re-enable write protection on the CPU.
  */
  write_cr0 (read_cr0 () | 0x10000);
}

/* begins the kernel spy */
static int __init interceptor_start(void) {
  /* Find the system call table */
  if(!(sys_call_table = find_sys_call_table())) {
    /* Well, that didn't work. 
       Cancel the module loading step. */
    return -1;
  }
  
  /* Store a copy of all the existing functions */
  ref_sys_cs3013_syscall2 = (void *)sys_call_table[__NR_cs3013_syscall2];

  /* Replace the existing system calls */
  disable_page_protection();
  sys_call_table[__NR_cs3013_syscall2] = (unsigned long *)new_sys_cs3013_syscall2;
  enable_page_protection();
  
  /* And indicate the load was successful */
  printk(KERN_INFO "Loaded interceptor!");

  return 0;
}

/* ends the kernel spy */
static void __exit interceptor_end(void) {
  /* If we don't know what the syscall table is, don't bother. */
  if(!sys_call_table)
    return;
  
  /* Revert all system calls to what they were before we began. */
  disable_page_protection();
  sys_call_table[__NR_cs3013_syscall2] = (unsigned long *)ref_sys_cs3013_syscall2;
  enable_page_protection();

  printk(KERN_INFO "Unloaded interceptor!");
}

MODULE_LICENSE("GPL");
module_init(interceptor_start);
module_exit(interceptor_end);

