/*Koning Yannick 312CB*/
#include "TStiva-L.h"
#include "TCoada-L.h"

#ifndef _TASK_
#define _TASK_

typedef struct
{
    unsigned int ID;
} Thread;

typedef struct
{
    unsigned int ID;
    Thread thread;
    unsigned int prio;
    unsigned int exec_t;
    unsigned int remain_t;
} Task;

// functions
void CreateThreadStack(void *s, size_t N); // create stack
void InsSortQ(void *q, Task t);            // sorted insert function
void add_task(void *q, int **available_id, int num_tasks, int exec_t,
              int prio, FILE *output);                                          // add_task function
void get_task(int ID, void *q_wait, void *q_run, void *q_finish, FILE *output); // get task function
void get_thread(int ID, void *q, void *s, FILE *output);                        // get thread function
int run(int time, int D, void *q_run, void *q_finished, void *q_wait,
        void *s_thread, int **available_id); // run function

// print functions
void print_wait(void *q, FILE *output);   // print waiting queue
void print_run(void *q, FILE *output);    // print running queue
void print_finish(void *q, FILE *output); // print finished queue

#endif