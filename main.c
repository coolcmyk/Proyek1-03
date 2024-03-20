#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include ".header/menu.h"
#include ".header/loading_screen.h"
#include ".header/py_exec.h"
#include <conio.h> 
int main() {
    Task tasks[MAX_TASKS];
    int num_tasks = 0;
    int choice;

    do {
        loadAnim();
        progressBar(5);
        display_menu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline

        switch(choice) {
            case 1:
                add_task(tasks, &num_tasks);
                break;
            case 2:
                view_tasks(tasks, num_tasks);
                break;
            case 3:
			    printf("Sort by SKS or Prioritize? (Enter '1' for SKS, '2' for Prioritize): ");
			    int sort_choice;
			    scanf("%d", &sort_choice);
			    getchar(); // Consume newline
			    if (sort_choice == 1) {
			        sort_tasks_by_SKS(tasks, num_tasks);
			    } else if (sort_choice == 2) {
			        sort_tasks_by_prioritize(tasks, num_tasks);
			    } else {
			        printf("Invalid choice. Please try again.\n");
			    }
			    break;

            case 4:
                search_task_by_name(tasks, num_tasks);
                break;
            case 5:
                save_tasks(tasks, num_tasks);
                break;
            case 6:
            	load_tasks(tasks, &num_tasks);
            	break;
            case 7:
                py_exec("python .header/StudyAI.py");
                break;
            case 8:
			    printf("\n");
			    printf("\t\t\t\t\t\t\t**User's Guide Summary**\n\n");
			    printf("\t\t\tThe Task Organizer is a versatile program designed to help you manage your tasks efficiently. With a simple and intuitive interface, it offers various features to streamline your task management process.\n\n");
			    printf("\t\t\tUpon launching the program, you are presented with a menu that provides options to perform different tasks such as adding new tasks, viewing existing tasks, sorting tasks based on different criteria, searching for tasks, saving tasks to a file, loading tasks from a file, and accessing the study assistant feature. Each option is clearly labeled and easy to navigate.\n\n");
			    printf("\t\t\tTo get started, simply follow the prompts provided by the program. You can add tasks by entering relevant information such as SKS (Study Credit Units), priority level, task name, and optional link. Tasks can be sorted based on SKS or priority, making it easier to prioritize your workload. Additionally, the search feature allows you to quickly find tasks by entering a partial task name. With the ability to save and load tasks from a file, you can easily backup your task list or transfer it between devices. Whether you're a student, professional, or anyone in need of task management assistance, the Task Organizer is a valuable tool to help you stay organized and productive.\n\n");
			    printf("\t\t\t---\n\n");
			    printf("Press backspace to terminate...\n");
			    while (1) {
			        if (_kbhit()) { // Check if a key is pressed
			            char ch = _getch(); // Get the pressed key
			            if (ch == '\b') { // Check if the pressed key is the backspace key
			                printf("\nBackspace key pressed. Terminating...\n");
			                break; // Terminate the loop
			            }
			        }
			    }
            case 9:
            	printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 9);

    return 0;
}
