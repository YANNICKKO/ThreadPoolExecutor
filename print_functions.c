/*Koning Yannick 312CB*/
#include "Task.h"

// print waititng queue
void print_wait(void *q, FILE *output)
{
    Task t;
    void *q_aux;
    q_aux = InitQ(sizeof(Task));

    fprintf(output, "====== Waiting queue =======\n");
    fprintf(output, "[");

    if (!VidaQ(q))
    {
        ExtrQ(q, &t);
        fprintf(output, "(%d: priority = %d, remaining_time = %d)", t.ID, t.prio, t.exec_t);
        IntrQ(q_aux, &t);
        while (!VidaQ(q))
        {
            Task aux;
            ExtrQ(q, &aux);
            fprintf(output, ",\n");
            fprintf(output, "(%d: priority = %d, remaining_time = %d)", aux.ID, aux.prio, aux.exec_t);
            IntrQ(q_aux, &aux);
        }
    }

    fprintf(output, "]\n");

    ConcatQ(q, q_aux);

    DistrQ(&q_aux);
}

// print running queue
void print_run(void *q, FILE *output)
{
    Task t;
    void *q_aux;
    q_aux = InitQ(sizeof(Task));

    fprintf(output, "====== Running in parallel =======\n");
    fprintf(output, "[");

    if (!VidaQ(q))
    {
        ExtrQ(q, &t);
        fprintf(output, "(%d: priority = %d, remaining_time = %d, running_thread = %d)", t.ID, t.prio, t.remain_t, t.thread.ID);
        IntrQ(q_aux, &t);
        while (!VidaQ(q))
        {
            Task aux;
            ExtrQ(q, &aux);
            fprintf(output, ",\n");
            fprintf(output, "(%d: priority = %d, remaining_time = %d, running_thread = %d)", aux.ID, aux.prio, aux.remain_t, aux.thread.ID);
            IntrQ(q_aux, &aux);
        }
    }

    fprintf(output, "]\n");

    ConcatQ(q, q_aux);

    DistrQ(&q_aux);
}

// print finished queue
void print_finish(void *q, FILE *output)
{
    Task t;
    void *q_aux;
    q_aux = InitQ(sizeof(Task));

    fprintf(output, "====== Finished queue =======\n");
    fprintf(output, "[");

    if (!VidaQ(q))
    {
        ExtrQ(q, &t);
        fprintf(output, "(%d: priority = %d, executed_time = %d)", t.ID, t.prio, t.exec_t);
        IntrQ(q_aux, &t);
        while (!VidaQ(q))
        {
            Task aux;
            ExtrQ(q, &aux);
            fprintf(output, ",\n");
            fprintf(output, "(%d: priority = %d, executed_time = %d)", aux.ID, aux.prio, aux.exec_t);
            IntrQ(q_aux, &aux);
        }
    }
    fprintf(output, "]\n");

    ConcatQ(q, q_aux);

    DistrQ(&q_aux);
}
