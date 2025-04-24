/*
    this file was an attempt to create a daily planned that is all terminal based 
    I believe it can hit a loop if the timing is incorrect, edge cases were not accounted for
    after I add this comment I plan to rewrite it to get it working, althouhg I plan to keep it simple, 
    i just dont want to add incorrect code without making some simple changes to get it working 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct task {
    int time;
    char name[20];
    int importance;
    char category[20];
};

struct taskList {
    int numTasks;
    struct task tasks[20];
};


int getTime() {
    int time;
    printf("How much time do you want to work on this task? ");
    scanf("%d", &time);
    return time;
}

struct task createTask() {
    struct task newTask;
    printf("Enter the name of the task: ");
    scanf("%s", newTask.name);
    printf("Enter the importance of the task (1-10): ");
    scanf("%d", &newTask.importance);
    printf("Enter the category of the task: ");
    scanf("%s", newTask.category);
    printf("Enter the time you want to work on this task: ");
    scanf("%d", &newTask.time);
    return newTask;
}


struct taskList createTaskList() {
    struct taskList newTaskList;
    printf("How many tasks do you want to add? ");
    scanf("%d", &newTaskList.numTasks);
    for (int i = 0; i < newTaskList.numTasks; i++) {
        newTaskList.tasks[i] = createTask();
    }
    return newTaskList;
}

void printTaskList(struct taskList taskList) {
    for (int i = 0; i < taskList.numTasks; i++) {
        printf("Task %d: %s, %d, %s, %d", i + 1, taskList.tasks[i].name, taskList.tasks[i].importance, taskList.tasks[i].category, taskList.tasks[i].time);
        printf("\n");
    }
}


void printTaskListImportance(struct taskList taskList) {
    for (int i = 0; i < taskList.numTasks; i++) {
        for (int j = 0; j < taskList.numTasks; j++) {
            if (taskList.tasks[i].importance > taskList.tasks[j].importance) {
                struct task temp = taskList.tasks[i];
                taskList.tasks[i] = taskList.tasks[j];
                taskList.tasks[j] = temp;
            }
        }
    }
    printTaskList(taskList);
}



void timeblocks() {
    int time[24];
    for (int i = 0; i < 24; i++) {
        time[i] = 0;
    }
    for (int i = 0; i < 24; i++) {
        if (i < 10) {
            printf("0%d:00", i);
        } else {
            printf("%d:00", i);
        }
        if (time[i] == 0) {
            printf(" - Free");
        } else {
            printf(" - Busy");
        }
        printf("\n");
    }
    struct taskList taskList = createTaskList();
    for (int i = 0; i < taskList.numTasks; i++) {
        int timeStart;
        printf("Enter the time you want to start working on %s: ", taskList.tasks[i].name);
        scanf("%d", &timeStart);
        for (int j = timeStart; j < timeStart + taskList.tasks[i].time; j++) {
            time[j] = 1;
        }
    }
    for (int i = 0; i < 24; i++) {
        if (i < 10) {
            printf("0%d:00", i);
        } else {
            printf("%d:00", i);
        }
        if (time[i] == 0) {
            printf(" - Free");
        } else {
            printf(" - Busy");
        }
        printf("\n");
    }

}


int main(int argc, char const *argv[])
{
    timeblocks();
    //struct taskList taskList = createTaskList();
    //printTaskListImportance(taskList);
    //printTaskList(taskList);


    //timeblocks();
    return 0;
}
