#include <iostream>
#include <string>
#include <vector>

// Priority labels
std::string PriorityList[] = { "highest", "high", "medium", "low", "lowest", "completed" };

// Task Class
class task
{
private:
    std::string feedback;

public:
    std::string title;
    std::string description;
    int priority;
    bool completion;

    // Proper Constructor
    task(std::string t, std::string d, int p, bool c)
    {
        title = t;
        description = d;
        priority = p;
        completion = c;
    }

    void display() {
        std::cout << "\nTitle: " << title << std::endl;
        std::cout << "Description: " << description << std::endl;
        std::cout << "Priority: " << PriorityList[priority] << std::endl;
        std::cout << "Completed: " << (completion ? "Yes" : "No") << std::endl;

        if (priority == 5) {
            std::cout << "Feedback: " << feedback << std::endl;
        }
    }

    void markCompleted() {
        completion = true;
        priority = 5;

        std::cout << "Please give feedback below: ";
        std::cin.ignore();
        std::getline(std::cin, feedback);
    }
};

// MAIN
int main()
{
    std::vector<task> priorityBuckets[6]; // 0–5 (including completed)

    int choice;

    while (true) {

        std::cout << "\n==== PROJECT MANAGER ====\n";
        std::cout << "1. Create new task\n";
        std::cout << "2. View tasks\n";
        std::cout << "3. Mark task completed\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter choice: ";

        std::cin >> choice;

        if (choice == 1) {

            std::string title, description;
            int priority;

            std::cin.ignore();

            std::cout << "Enter title: ";
            std::getline(std::cin, title);

            std::cout << "Enter description: ";
            std::getline(std::cin, description);

            std::cout << "\nSelect priority:\n";
            for (int i = 0; i < 5; i++) {
                std::cout << i << ". " << PriorityList[i] << std::endl;
            }

            std::cin >> priority;

            if (priority < 0 || priority > 4) {
                std::cout << "Invalid priority!\n";
                continue;
            }

            task newTask(title, description, priority, false);

            priorityBuckets[priority].push_back(newTask);

            std::cout << "Task created successfully!\n";
        }

        else if (choice == 2) {

            for (int i = 0; i < 6; i++) {
                std::cout << "\n--- " << PriorityList[i] << " ---\n";

                for (int j = 0; j < priorityBuckets[i].size(); j++) {
                    std::cout << "\nTask #" << j << std::endl;
                    priorityBuckets[i][j].display();
                }
            }
        }

        else if (choice == 3) {

            int p, index;

            std::cout << "Enter priority of task: ";
            std::cin >> p;

            std::cout << "Enter task index: ";
            std::cin >> index;

            if (p < 0 || p > 4 || index < 0 || index >= priorityBuckets[p].size()) {
                std::cout << "Invalid selection!\n";
                continue;
            }

            task completedTask = priorityBuckets[p][index];
            priorityBuckets[p].erase(priorityBuckets[p].begin() + index);

            completedTask.markCompleted();
            priorityBuckets[5].push_back(completedTask);

            std::cout << "Task marked as completed!\n";
        }

        else if (choice == 4) {
            break;
        }

        else {
            std::cout << "Invalid option!\n";
        }
    }

    return 0;
}
