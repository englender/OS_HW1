//
// Created by Dell on 4/7/2019.
//

#include "hw1_syscalls.h"


<<<<<<< HEAD
=======
#define LOGSIZE 100

>>>>>>> a9845be47f6a88478b7b6bd0698edcb685fc32c3
int sys_sc_restrict (pid_t pid ,int proc_restriction_level, scr* restrictions_list,
                 int list_size){
    if(pid<0){
        return -ESRCH;
    }

    task_t* p=find_task_by_pid(pid);                    //dan - if task_t doesn't work, try task_struct
    if(p == NULL){
        return -ESRCH;
    }
    if(proc_restriction_level<0 || proc_restriction_level>2){
        return -EINVAL;
    }
    if( list_size<0){
        return -EINVAL;
    }
    if(p->scr_list!=NULL){
        kfree(p->scr_list);
    }

    p->scr_list=kmalloc(sizeof(scr)*list_size);
    if(p->scr_list==NULL)
        return -ENOMEM;

    if(copy_from_user(p->scr_list,restrictions_list, sizeof(scr)*list_size)!=0){
        kfree(p->scr_list);
        return -ENOMEM;
    }

    p->forbidden_log=kmalloc(sizeof(fai)*LOGSIZE);
    if(p->forbidden_log==NULL)
/* roni - should we free the scr_list??*/
        return -ENOMEM;

    p->restriction_level=proc_restriction_level;
    p->scr_list_size=list_size;
    return 0;
}


int sys_set_proc_restriction (pid_t pid ,int proc_restriction_level){

    if(pid<0){
        return -ESRCH;
    }

    task_t* p=find_task_by_pid(pid);                    //dan - if task_t doesn't work, try task_struct
    if(p == NULL){
        return -ESRCH;
    }

    if(proc_restriction_level<0 || proc_restriction_level>2){
        return -EINVAL;
    }

    p->restriction_level=proc_restriction_level;
    return 0;
}


int sys_get_process_log(pid_t pid, int size, fai* user_mem){

    if(pid<0){
        return -ESRCH;
    }
    task_t* p=find_task_by_pid(pid);                    //dan - if task_t doesn't work, try task_struct
    if(p == NULL){
        return -ESRCH;
    }
    if(size> p->forbidden_log_size){
        return -EINVAL;
    }
    if(size<0){
        return -EINVAL;
    }

    fai* ptr=p->forbidden_log+forbidden_log_size-size;
    if(copy_to_user(user_mem,ptr, sizeof(fai)*size)!=0){       //need to update source of copy_to_user
       return -ENOMEM;
    }
    return 0;
}