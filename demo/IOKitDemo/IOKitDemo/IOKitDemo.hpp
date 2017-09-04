/* add your code here */
/* add your code here */
#include <mach/mach_types.h>
#include <libkern/libkern.h>

kern_return_t HelloStart(kmod_info_t *ki ,void *d){
    
    printf("hello kern World!");
    
    return KERN_SUCCESS;
};

kern_return_t HelloStop(kmod_info_t *ki ,void *d){
    
    printf("goodbye kern world!");
    
    return KERN_SUCCESS;
};

/**
 sudo chown -R root:wheel IOKitDemo.kext
 sudo kextload IOKitDemo.kext
 kextstat
 sudo kextunload IOKitDemo.kext
 
 /private/var/folders/mc/pbqmgp513ybc4f860d3w3thw0000gn/T/TemporaryItems/(A Document Being Saved By Xcode 4)/CleanBuildFolderInProgress/Products/Debug/IOKitDemo.kext failed to load - (libkern/kext) not loadable (reason unspecified); check the system/kernel logs for errors or try kextutil(8).
 
 */
