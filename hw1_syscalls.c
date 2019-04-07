//
// Created by Dell on 4/7/2019.
//

#include <linux/sched.h>
#include <linux/errno.h>

#define

int sc_restrict (pid_t pid ,int proc_restriction_level, scr* restrictions_list, int list_size){
    if(pid<0){
        return=-ESRCH;
    }


}