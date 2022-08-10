/*Koning Yannick 312CB*/
#include "Task.h"

// create stack with N items with IDs from N to 0
void CreateThreadStack(void *s, size_t N)
{
    Thread t;

    for (; N > 0;)
    {
        t.ID = --N;

        if (!Push(s, &t))
            return;
    }
}

// sorted insert function
void InsSortQ(void *q, Task t)
{
    void *q_aux;
    q_aux = InitQ(sizeof(Task));
    int ok = 0;

    while (!VidaQ(q))
    {
        Task aux;
        ExtrQ(q, &aux);

        // if it has less prio
        // then higher exec_t
        // then higher id
        //==============
        if (aux.prio < t.prio && ok == 0)
        {
            IntrQ(q_aux, &t);
            ok = 1;
        }
        else if (aux.prio == t.prio && ok == 0)
        {
            if (aux.exec_t > t.exec_t)
            {
                IntrQ(q_aux, &t);
                ok = 1;
            }
            else if (aux.exec_t == t.exec_t)
            {
                if (aux.ID > t.ID)
                {
                    IntrQ(q_aux, &t);
                    ok = 1;
                }
            }
        }
        //================

        IntrQ(q_aux, &aux);
    }
    // if its empty
    if (ok == 0)
    {
        IntrQ(q_aux, &t);
    }

    ConcatQ(q, q_aux);

    DistrQ(&q_aux);
}

// add_task function
void add_task(void *q, int **available_id, int num_tasks, int exec_t, int prio, FILE *output)
{
    Task t;
    int ID = 0;

    for (; num_tasks > 0; num_tasks--)
    {
        t.exec_t = exec_t;
        t.remain_t = exec_t;
        t.prio = prio;

        // if an available id is found
        while ((*available_id)[ID] != 0)
        {
            ID++;
        }
        (*available_id)[ID] = 1;
        t.ID = ++ID;

        InsSortQ(q, t);

        fprintf(output, "Task created successfully : ID %d.\n", ID);
    }
}

// get task function
void get_task(int ID, void *q_wait, void *q_run, void *q_finish, FILE *output)
{
    int ok = 0;
    void *q_aux;
    q_aux = InitQ(sizeof(Task));
    if (ok == 0)
    {
        Task t;
        while (ExtrQ(q_run, &t))
        {
            // if the ID is found in the running queue
            if (t.ID == ID && ok == 0)
            {
                fprintf(output, "Task %d is running (remaining_time = %d).\n", ID, t.exec_t);
                ok = 1;
            }
            IntrQ(q_aux, &t);
        }
        ConcatQ(q_run, q_aux);
    }
    if (ok == 0)
    {
        Task t;
        while (ExtrQ(q_wait, &t))
        {
            // if the ID is found in the waiting queue
            if (t.ID == ID && ok == 0)
            {
                fprintf(output, "Task %d is waiting (remaining_time = %d).\n", ID, t.exec_t);
                ok = 1;
            }
            IntrQ(q_aux, &t);
        }
        ConcatQ(q_wait, q_aux);
    }
    if (ok == 0)
    {
        Task t;
        while (ExtrQ(q_finish, &t))
        {
            // if the ID is found in the finished queue
            if (t.ID == ID && ok == 0)
            {
                fprintf(output, "Task %d is finished (executed_time = %d).\n", ID, t.exec_t);
                ok = 1;
            }
            IntrQ(q_aux, &t);
        }
        ConcatQ(q_finish, q_aux);
    }
    if (ok == 0)
        // if the ID is not found
        fprintf(output, "Task %d not found.\n", ID);

    DistrQ(&q_aux);
}

// get thread function
void get_thread(int ID, void *q, void *s, FILE *output)
{
    void *q_aux;
    q_aux = InitQ(sizeof(Task));
    void *s_aux;
    s_aux = InitS(sizeof(Thread));
    int ok = 0;
    if (ok == 0)
    {
        while (!VidaS(s))
        {
            Thread thread;
            Pop(s, &thread);
            // if the ID is found in the thread stack
            if (thread.ID == ID && ok == 0)
            {
                fprintf(output, "Thread %d is idle.\n", ID);
                ok = 1;
            }
            Push(s_aux, &thread);
        }
        Rastoarna(s, s_aux);
    }
    if (ok == 0)
    {
        while (!VidaQ(q))
        {
            Task t;
            ExtrQ(q, &t);
            // if the ID is found in the running queue
            if (t.thread.ID == ID && ok == 0)
            {
                fprintf(output, "Thread %d is running task %d (remaining_time = %d).\n", ID, t.ID, t.remain_t);
                ok = 1;
            }
            IntrQ(q_aux, &t);
        }
        ConcatQ(q, q_aux);
    }

    DistrQ(&q_aux);
    DistrS(&s_aux);
}

// run function
int run(int time, int D, void *q_run, void *q_finished, void *q_wait, void *s_thread, int **available_id)
{
    Thread thread1;
    Task task1;

    int total_time = 0, total_time_aux = 0;
    // if the time is higher than D
    if (time > D)
    {
        // run until time runs out
        while (time >= D)
        {
            // calculate total time
            total_time_aux = run(D, D, q_run, q_finished, q_wait, s_thread, available_id);
            // if a higher total time is found replace it
            if (total_time_aux > total_time)
                total_time = total_time_aux;
            time -= D;
        }
        // run one last time
        if (time >= 0)
        {
            // calculate total time
            total_time += run(time, D, q_run, q_finished, q_wait, s_thread, available_id);
            // if a higher total time is found replace it
            if (total_time_aux > total_time)
                total_time = total_time_aux;
        }
        return total_time;
    }

    // put tasks on the running queue
    while (!VidaQ(q_wait) && !VidaS(s_thread))
    {
        Pop(s_thread, &thread1);
        ExtrQ(q_wait, &task1);
        task1.thread.ID = thread1.ID;
        InsSortQ(q_run, task1);
    }

    Task task;
    void *q_aux;
    q_aux = InitQ(sizeof(Task));
    int ok = 0;

    // run for each task
    while (ExtrQ(q_run, &task))
    {
        int time_remain = task.remain_t - time;
        // if the task ended we put it on the finished queue
        // and make the ID available
        if (time_remain <= 0)
        {
            Thread thread;
            thread.ID = task.thread.ID;
            Push(s_thread, &thread);
            IntrQ(q_finished, &task);
            (*available_id)[task.ID - 1] = 0;

            // if a higher total time is found replace it
            if (ok == 0 || total_time < task.exec_t)
            {
                total_time = task.exec_t;
                ok = 1;
            }
        }
        else
        {
            task.remain_t = task.remain_t - time;
            IntrQ(q_aux, &task);
        }
    }
    ConcatQ(q_run, q_aux);

    DistrQ(&q_aux);

    Thread thread2;
    Task task2;
    // put tasks on the running queue
    while (!VidaQ(q_wait) && !VidaS(s_thread))
    {
        Pop(s_thread, &thread2);
        ExtrQ(q_wait, &task2);
        task1.thread.ID = thread2.ID;
        InsSortQ(q_run, task2);
    }

    return total_time;
}