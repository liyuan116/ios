//
//  GKEDemo.c
//  GKEDemo
//
//  Created by liyuan on 2017/9/3.
//  Copyright © 2017年 liyuan. All rights reserved.
//

#include <mach/mach_types.h>

kern_return_t GKEDemo_start(kmod_info_t * ki, void *d);
kern_return_t GKEDemo_stop(kmod_info_t *ki, void *d);

kern_return_t GKEDemo_start(kmod_info_t * ki, void *d)
{
    return KERN_SUCCESS;
    
}

kern_return_t GKEDemo_stop(kmod_info_t *ki, void *d)
{
    return KERN_SUCCESS;
}
