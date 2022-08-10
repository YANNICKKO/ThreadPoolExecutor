/*Koning Yannick 312CB*/
#include "Task.h"

#define MaxTask 1 << 13

int main(int argc, char *argv[])
{
    FILE *input;
    input = fopen(argv[1], "rt");
    FILE *output;
    output = fopen(argv[2], "wt");

    // number of threads and quantum of time
    int D, C, N;
    fscanf(input, "%d", &D);
    fscanf(input, "%d", &C);
    N = C * 2;

    // init stack of threads with their id-s and init the 3 queues
    void *s_thread, *q_wait, *q_run, *q_finished;

    // stack
    s_thread = InitS(sizeof(Thread));
    CreateThreadStack(s_thread, N);

    // 3 queues
    q_wait = InitQ(sizeof(Task));
    q_run = InitQ(sizeof(Task));
    q_finished = InitQ(sizeof(Task));

    // read
    char *line = malloc(256);
    int *available_id = calloc(MaxTask, sizeof(int));
    int total_time = 0;

    while (fgets(line, 256, input))
    {
        char *instr = strtok(line, " ");

        if (!strcmp(instr, "add_tasks"))
        {
            // get the 3 numbers
            char *string1, *string2, *string3;
            string1 = strtok(NULL, " ");
            string2 = strtok(NULL, " ");
            string3 = strtok(NULL, " ");

            int num_tasks, exec_t, prio;
            num_tasks = atoi(string1);
            exec_t = atoi(string2);
            prio = atoi(string3);

            add_task(q_wait, &available_id, num_tasks, exec_t, prio, output);
        }
        else if (!strcmp(instr, "get_task"))
        {
            // get the task ID
            char *string1;
            string1 = strtok(NULL, " ");

            int ID;
            ID = atoi(string1);

            get_task(ID, q_wait, q_run, q_finished, output);
        }
        else if (!strcmp(instr, "get_thread"))
        {
            // get the thread ID
            char *string1;
            string1 = strtok(NULL, " ");

            int ID;
            ID = atoi(string1);
            if (ID < N)
                get_thread(ID, q_run, s_thread, output);
        }
        else if (!strcmp(instr, "run"))
        {
            char *string1;
            string1 = strtok(NULL, " ");

            int time;
            time = atoi(string1);
            fprintf(output, "Running tasks for %d ms...\n", time);

            total_time += run(time, D, q_run, q_finished, q_wait, s_thread, &available_id);
        }
        else if (!strcmp(instr, "print"))
        {
            char *string1;
            string1 = strtok(NULL, " \n");
            if (!strcmp(string1, "waiting"))
                print_wait(q_wait, output);
            else if (!strcmp(string1, "running"))
                print_run(q_run, output);
            else if (!strcmp(string1, "finished"))
                print_finish(q_finished, output);
        }
        else if (!strcmp(instr, "finish\n"))
        {
            // run till the queues are empty
            while (!VidaQ(q_run) || !VidaQ(q_wait))
            {
                total_time += run(D, D, q_run, q_finished, q_wait, s_thread, &available_id);
            }
            fprintf(output, "Total time: %d", total_time);
            break;
        }
    }

    // close the files, free what is allocated and destroy the queueus and stack
    fclose(input);
    fclose(output);

    free(line);
    free(available_id);

    DistrS(&s_thread);
    DistrQ(&q_wait);
    DistrQ(&q_run);
    DistrQ(&q_finished);

    return 0;
}