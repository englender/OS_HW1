//
// Created by ronien on 08/04/2019.
//

#ifndef CLION_HW1_SYSCALLS_H
#define CLION_HW1_SYSCALLS_H

#include <linux/sched.h>
#include <linux/errno.h>
#include <linux/slab.h>             //for copy_to/from_user
#include <asm/uaccess.h>            //for copy_to/from_user


int sc_restrict (pid_t pid ,int proc_restriction_level, scr* restrictions_list, int list_size) {
    int res;
    __asm__(
    "int $0x80;"
    : "=a" (res)
    : "0" (243), "b" (pid), "c" (proc_restriction_level), "d" (restrictions_list), "S" (list_size)
    :"memory"
    );
    if ((res) < 0) {
        errno = (-res);
        return -1;
    }
    return res;
}

int set_proc_restriction (pid_t pid ,int proc_restriction_level){
    int res;
    __asm__(
    "int $0x80;"
    : "=a" (res)
    : "0" (244), "b" (pid), "c" (proc_restriction_level)
    :"memory"
    );
    if ((res) < 0) {
        errno = (-res);
        return -1;
    }
    return res;
}

int get_process_log(pid_t pid, int size, fai* user_mem){
    int res;
    __asm__(
    "int $0x80;"
    : "=a" (res)
    : "0" (245), "b" (pid), "c" (size), "d" (user_mem)
    :"memory"
    );
    if ((res) < 0) {
        errno = (-res);
        return -1;
    }
    return res;
}

#endif //CLION_HW1_SYSCALLS_H
