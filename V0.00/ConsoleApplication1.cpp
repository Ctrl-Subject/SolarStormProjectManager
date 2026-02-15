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


        //Makes sure input is a number shown above
        while (!(std::cin >> choice)) {

            std::cout << "Invalid option! \nEnter Choice: ";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }

        //chooses function to do
        switch (choice) {

        case 1: { //creates new task

            std::string title, description;
            int priority;
            std::cin.ignore();

            //asks for inputs
            //title
            std::cout << "Enter title: ";
            std::getline(std::cin, title);

            //description
            std::cout << "Enter description: ";
            std::getline(std::cin, description);

            //Priority
            std::cout << "\nSelect priority:\n";
            for (int i = 0; i < 5; i++) {
                std::cout << i << ". " << PriorityList[i] << std::endl;
            }

            //Makes sure input is a number and is in list above
            while ((!(std::cin >> priority)) || (priority < 0 || priority > 4)) {

                std::cout << "Invalid option! \nEnter Choice: ";
                std::cin.clear();
                std::cin.ignore(10000, '\n');
            };

            //creates new task
            task newTask(title, description, priority, false);
            
            //adds task to tasklist
            priorityBuckets[priority].push_back(newTask);
            std::cout << "Task created successfully!\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            break;
        }

        case 2: { //displays all tasks with priotities
            for (int i = 0; i < 6; i++) {
                std::cout << "\n--- " << PriorityList[i] << " ---\n";

                for (int j = 0; j < priorityBuckets[i].size(); j++) {
                    std::cout << "\nTask #" << j << std::endl;
                    priorityBuckets[i][j].display();
                }
            }
            break;
        }

        case 3: { //looks for task to mark as complete
            int p, index;

            //Priority
            std::cout << "\nSelect priority:\n";
            for (int i = 0; i < 5; i++) {
                std::cout << i << ". " << PriorityList[i] << std::endl;
            }

            //checks which list it's in
            std::cout << "Enter priority of task: ";
            //Makes sure input is a number shown above
            while (!(std::cin >> p)) {

                std::cout << "Invalid option! \nEnter Choice: ";
                std::cin.clear();
                std::cin.ignore(10000, '\n');
            }


            //checks index of list p
            std::cout << "Enter task index: ";
            //Makes sure input is a number 
            while (!(std::cin >> index) && (index < 0 || index >= priorityBuckets[p].size())) {

                std::cout << "Invalid option! \nEnter Choice: ";
                std::cin.clear();
                std::cin.ignore(10000, '\n');
            }

            if (index < 0 || index >= priorityBuckets[p].size()) {
                std::cout << "no task found";
                break;
            }

            task completedTask = priorityBuckets[p][index];
            priorityBuckets[p].erase(priorityBuckets[p].begin() + index);

            completedTask.markCompleted();
            priorityBuckets[5].push_back(completedTask);

            std::cout << "Task marked as completed!\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            break;
        }

        case 4: { //closes program
            std::abort();
        }

        default: {
            std::cout << "Invalid option!\n";
            std::cin.ignore();
            std::cin.clear();
        }

        }
    }

    return 0;
}
