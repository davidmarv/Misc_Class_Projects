#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TASKS 20
#define MAX_NAME_LEN 50
#define MAX_CATEGORY_LEN 50
#define MAX_HOURS 24

struct task {
    int time;
    char name[MAX_NAME_LEN];
    int importance;
    char category[MAX_CATEGORY_LEN];
};

struct taskList {
    int numTasks;
    struct task tasks[MAX_TASKS];
};

void readString(char *prompt, char *buffer, int length) {
    printf("%s", prompt);
    fgets(buffer, length, stdin);
    buffer[strcspn(buffer, "\n")] = 0; 
}

int readInt(char *prompt, int min, int max) {
    int value;
    char buffer[50];
    while (1) {
        printf("%s", prompt);
        fgets(buffer, sizeof(buffer), stdin);
        if (sscanf(buffer, "%d", &value) == 1 && value >= min && value <= max) {
            return value;
        } else {
            printf("Please enter a number between %d and %d.\n", min, max);
        }
    }
}

struct task createTask() {
    struct task newTask;

    readString("Enter the name of the task: ", newTask.name, MAX_NAME_LEN);
    newTask.importance = readInt("Enter the importance of the task (1-10): ", 1, 10);
    readString("Enter the category of the task: ", newTask.category, MAX_CATEGORY_LEN);
    newTask.time = readInt("Enter the number of hours to work on this task (1-24): ", 1, 24);

    return newTask;
}

struct taskList createTaskList() {
    struct taskList newList;
    newList.numTasks = readInt("\n How many tasks do you want to add (1–20)? \n", 1, MAX_TASKS);
    for (int i = 0; i < newList.numTasks; i++) {
        printf("\n--- Task %d ---\n", i + 1);
        newList.tasks[i] = createTask();
    }
    return newList;
}

void printTaskList(const struct taskList *list) {
    printf("\n--- Task List ---\n");
    for (int i = 0; i < list->numTasks; i++) {
        struct task t = list->tasks[i];
        printf("Task %d: %s | Importance: %d | Category: %s | Time: %d hour(s)\n",
               i + 1, t.name, t.importance, t.category, t.time);
    }
}

void sortTasksByImportance(struct taskList *list) {
    for (int i = 0; i < list->numTasks - 1; i++) {
        for (int j = i + 1; j < list->numTasks; j++) {
            if (list->tasks[j].importance > list->tasks[i].importance) {
                struct task temp = list->tasks[i];
                list->tasks[i] = list->tasks[j];
                list->tasks[j] = temp;
            }
        }
    }
}

void displayTimeblocks(int timeBlocks[]) {
    printf("\n--- Daily Schedule ---\n");
    for (int i = 0; i < MAX_HOURS; i++) {
        printf("%02d:00 - %s\n", i, timeBlocks[i] ? "Busy" : "Free");
    }
}

void timeblocks() {
    int schedule[MAX_HOURS] = {0};
    struct taskList list = createTaskList();

    for (int i = 0; i < list.numTasks; i++) {
        printf("enter start time for task: ");
        int startTime = readInt(
            list.tasks[i].name,
            0,
            MAX_HOURS - list.tasks[i].time
        );
        int conflict = 0;

        for (int j = 0; j < list.tasks[i].time; j++) {
            if (schedule[startTime + j]) {
                conflict = 1;
                break;
            }
        }

        if (conflict) {
            printf(" Time slot conflict for task '%s'. Skipping.\n", list.tasks[i].name);
            continue;
        }

        for (int j = 0; j < list.tasks[i].time; j++) {
            schedule[startTime + j] = 1;
        }
    }

    displayTimeblocks(schedule);
    sortTasksByImportance(&list);
    printTaskList(&list);
}

int main() {
    timeblocks();
    return 0;
}
