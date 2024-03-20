#define MAX_TASKS 100
#define MAX_NAME_LENGTH 50
#define MAX_LINK_LENGTH 100
#define MAX_TASKS 100
#define MAX_NAME_LENGTH 50
#define MAX_LINK_LENGTH 100
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "py_exec.h"
#include <ctype.h>
#include "loading_screen.h"
#include <unistd.h>
#include <windows.h> 
#define MAX_FRAMES 15
#define MAX_FRAME_LENGTH 1000
typedef struct {
    int SKS;
    int prioritize;
    char name[MAX_NAME_LENGTH];
    char link[MAX_LINK_LENGTH];
} Task;

// Function prototypes
void display_menu();
void add_task(Task tasks[], int *num_tasks);
void view_tasks(Task tasks[], int num_tasks);
void save_tasks(Task tasks[], int num_tasks);
void sort_tasks_by_SKS(Task tasks[], int num_tasks);
void sort_tasks_by_prioritize(Task tasks[], int num_tasks);

void loadAnim() {
    system("cls"); // Clear the screen
    system("type .\\.header\\ascii.txt");
}
void loadMenu(){
    system("cls"); // Clear the screen
    system("type .\\.header\\asciimenu.txt");
}
void progressBar(int total) {
    const int width = 20; // Width of the progress bar
    const char progressChar = '='; // Character representing progress
    const char emptyChar = '-'; // Character representing empty space

    for (int i = 0; i <= total; i++) {
        // Calculate progress percentage
        double progressPercentage = (double)i / total;
        
        // Calculate the number of progress characters to print
        int progressChars = (int)(progressPercentage * width);
        
        // Print the progress bar
        printf("[");
        for (int j = 0; j < width; j++) {
            if (j < progressChars) {
                printf("%c", progressChar);
            } else {
                printf("%c", emptyChar);
            }
        }
        printf("] %.1f%%\r", progressPercentage * 100);
        fflush(stdout); // Flush the output buffer to update the progress bar immediately
        
        usleep(100000); // Sleep for 100 milliseconds (adjust for desired speed)
    }
    printf("\n");
}
int py_exec(const char *str) {
    return system(str);
}
// Function to display the menu
void display_menu() {
    //using system("cls") to clear out previous usage of the program
    system("cls");
    loadMenu();
    printf("\n");
    printf("\t /////////////////////////////////\n");
    printf("\t |           Main Menu           |\n");
    printf("\t /////////////////////////////////\n\n");
    printf("\t [1] Add Task\n");
    printf("\t [2] View Tasks\n");
    printf("\t [3] Sort Tasks\n");
    printf("\t [4] Search Tasks\n");
    printf("\t [5] Save Tasks\n");
    printf("\t [6] Load Tasks\n");
    printf("\t [7] Study Assistant\n");
    printf("\t [8] User's Guide\n");
    printf("\t [9] Exit Program\n\n");
    printf("\t /////////////////////////////////\n\n");

}

//utilization of strcasestr because the library doesn't provide one
char *strcasestr(const char *haystack, const char *needle) {
    if (!*needle) return (char *)haystack;

    for (; *haystack; ++haystack) {
        if (toupper(*haystack) == toupper(*needle)) {
            const char *h, *n;
            for (h = haystack, n = needle; *h && *n; ++h, ++n) {
                if (toupper(*h) != toupper(*n)) break;
            }
            if (!*n) return (char *)haystack;
        }
    }

    return NULL;
}
// Function to add a task
void add_task(Task tasks[], int *num_tasks) {
    if (*num_tasks >= MAX_TASKS) {
        printf("Cannot add more tasks. Task list is full.\n");
        return;
    }

    Task new_task;

    printf("Enter SKS: ");
    scanf("%d", &new_task.SKS);
    getchar(); // Consume newline

    printf("Enter Priority: ");
    scanf("%d", &new_task.prioritize);
    getchar(); // Consume newline

    printf("Enter Task Name: ");
    fgets(new_task.name, MAX_NAME_LENGTH, stdin);
    new_task.name[strcspn(new_task.name, "\n")] = '\0'; // Remove trailing newline

    printf("Enter Link: ");
    fgets(new_task.link, MAX_LINK_LENGTH, stdin);
    new_task.link[strcspn(new_task.link, "\n")] = '\0'; // Remove trailing newline

    tasks[*num_tasks] = new_task;
    (*num_tasks)++;

    printf("Task added successfully!\n");
    system("pause");
}

// Function to view all tasks
void view_tasks(Task tasks[], int num_tasks) {
    if (num_tasks == 0) {
        printf("No tasks added yet.\n");
        return;
    }

    printf("\n===== Tasks =====\n");
    for (int i = 0; i < num_tasks; i++) {
        printf("Task %d:\n", i + 1);
        printf("SKS: %d\n", tasks[i].SKS);
        printf("Priority: %d\n", tasks[i].prioritize);
        printf("Name: %s\n", tasks[i].name);
        printf("Link: %s\n\n", tasks[i].link);
    }
    system("pause");
}

// Function to save tasks to a file
void save_tasks(Task tasks[], int num_tasks) {
    FILE *file = fopen("tasks.txt", "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    //iteration for every tasks that was added to the program
    for (int i = 0; i < num_tasks; i++) {
        fprintf(file, "Task %d:\n", i + 1);
        fprintf(file, "SKS: %d\n", tasks[i].SKS);
        fprintf(file, "Priority: %d\n", tasks[i].prioritize);
        fprintf(file, "Name: %s\n", tasks[i].name);
        fprintf(file, "Link: %s\n\n", tasks[i].link);
    }

    fclose(file);
    printf("Tasks saved to tasks.txt successfully!\n");
    system("pause");
}

// Function to sort tasks by SKS
void sort_tasks_by_SKS(Task tasks[], int num_tasks) {
    int i, j;
    Task temp;

    for (i = 0; i < num_tasks - 1; i++) {
        for (j = 0; j < num_tasks - i - 1; j++) {
            if (tasks[j].SKS < tasks[j + 1].SKS) {
                temp = tasks[j];
                tasks[j] = tasks[j + 1];
                tasks[j + 1] = temp;
            }
        }
    }

    printf("Tasks sorted by SKS.\n");
    system("pause");
    system("cls");
    view_tasks(tasks, num_tasks);
}

// Function to sort tasks by prioritize
void sort_tasks_by_prioritize(Task tasks[], int num_tasks) {
    int i, j;
    Task temp;

    //utilization of bubble sort to sort based on task struct's prioritze property
    for (i = 0; i < num_tasks - 1; i++) {
        for (j = 0; j < num_tasks - i - 1; j++) {
            if (tasks[j].prioritize > tasks[j + 1].prioritize) {
                temp = tasks[j];
                tasks[j] = tasks[j + 1];
                tasks[j + 1] = temp;
            }
        }
    }

    printf("Tasks sorted by Prioritize.\n");
    system("pause");
    system("cls");
    view_tasks(tasks, num_tasks);
}

int load_tasks(Task tasks[], int *num_tasks) {
    FILE *file = fopen("tasks.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 0; // Return 0 to indicate failure
    }

    // Temporary variables to read data from the file
    int SKS, prioritize;
    char name[MAX_NAME_LENGTH];
    char link[MAX_LINK_LENGTH];

    int tasks_loaded = 0; // Counter to keep track of tasks loaded

    // Loop through each line in the file and read task data
    while (fscanf(file, "Task %*d:\nSKS: %d\nPriority: %d\nName: %[^\n]\nLink: %[^\n]\n\n",
                  &SKS, &prioritize, name, link) == 4) {
        // Check if the loaded task already exists in the current tasks array
        int duplicate = 0;
        for (int i = 0; i < *num_tasks; i++) {
            if (strcmp(tasks[i].name, name) == 0 && strcmp(tasks[i].link, link) == 0) {
                printf("Duplicate task detected: %s\n", name);
                duplicate = 1;
                break;
            }
        }

        // If the task is not a duplicate, add it to the tasks array
        if (!duplicate) {
            Task new_task;
            new_task.SKS = SKS;
            new_task.prioritize = prioritize;
            strcpy(new_task.name, name);
            strcpy(new_task.link, link);

            tasks[*num_tasks] = new_task;
            (*num_tasks)++;
            tasks_loaded++;
        }
    }

    fclose(file);
    printf("Tasks loaded from tasks.txt: %d\n", tasks_loaded);
    return tasks_loaded; // Return the number of tasks loaded
}

void open_link(const char *link) {
    char command[100]; // Assuming the command length won't exceed 100 characters
    sprintf(command, "start \"\" \"%s\"", link);
    system(command);
}

// Function to search tasks by name (case-insensitive and partial match)
void search_task_by_name(Task tasks[], int num_tasks) {
    char search_name[MAX_NAME_LENGTH];
    printf("Enter the name of the task: ");
    fgets(search_name, MAX_NAME_LENGTH, stdin);
    search_name[strcspn(search_name, "\n")] = '\0'; // Remove trailing newline

    // Variable to track if any task is found
    int found = 0;

    for (int i = 0; i < num_tasks; i++) {
        if (strcasestr(tasks[i].name, search_name) != NULL) {
            printf("Task %d:\n", i + 1);
            printf("SKS: %d\n", tasks[i].SKS);
            printf("Priority: %d\n", tasks[i].prioritize);
            printf("Name: %s\n", tasks[i].name);
            printf("Link: %s\n\n", tasks[i].link);
            found = 1; // Set found to true if at least one task is found
        }
    }

    if (!found) {
        printf("No tasks found matching the search criteria.\n");
    } else {
        // Prompt the user whether to open the link associated with a task
        char choice;
        printf("Do you want to open the link associated with any task? (y/n): ");
        scanf(" %c", &choice); // Note the space before %c to consume the newline character
        if (choice == 'y' || choice == 'Y') {
            printf("Enter the task number to open its link: ");
            int task_number;
            scanf("%d", &task_number);
            getchar(); // Consume newline
            if (task_number >= 1 && task_number <= num_tasks) {
                open_link(tasks[task_number - 1].link);
            } else {
                //error handling
                printf("Invalid task number.\n");
            }
        }
    }
    system("pause");
}


