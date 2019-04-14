//
// Created by ronien on 08/04/2019.
//
#include <linux/sched.h>
#include <linux/jiffies.h>              //should it be here??

int sys_restrict(int sys_num){
    scr* ptr;

    for(int i=0; i<current->list_size; i++){
        ptr=current->scr_list+i;
        if(ptr->syscall_num==sys_num && current->restriction_level < ptr->restriction_threshold){
            if(current->forbidden_log_size==100)
                array_shift_left();

            current->forbidden_log[current->forbidden_log_size]->syscall_num=sys_num;
            current->forbidden_log[current->forbidden_log_size]->syscall_restriction_threshold=ptr->restriction_threshold;
            current->forbidden_log[current->forbidden_log_size]->proc_restriction_level=current->restriction_level;
            current->forbidden_log[current->forbidden_log_size]->time=jiffies;

            current->forbidden_log_size++;
            return -1;
        }
    }

    return 0;           //if syscall is not restricted
}


void array_shift_left(){
    for (int i = 1; i < current->forbidden_log_size; i++) {
        current->forbidden_log[i-1]=current->forbidden_log[i];
    }
    current->forbidden_log_size--;
}