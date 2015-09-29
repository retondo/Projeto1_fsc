#ifndef PCB_H_
#define PCB_H_

typedef struct info_process {
    char name[30];
    long segment_id;
    int priority;
    long segment_size;
} pcb;

#endif
