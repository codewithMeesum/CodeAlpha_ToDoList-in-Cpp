#include<iostream>
#include<vector>
#include<fstream>
using namespace std;
class Task {
public:
    string title;
    bool completed;
};
void saveTasks(vector<Task>& tasks)
{
    ofstream file("tasks.txt");

    for(int i = 0; i < tasks.size(); i++)
    {
        file << tasks[i].title << "|" << tasks[i].completed << endl;
    }

    file.close();
}
void loadTasks(vector<Task>& tasks)
{
    ifstream file("tasks.txt");

    if(!file)
        return;

    Task temp;
    string status;

    while(getline(file, temp.title, '|'))
    {
        getline(file, status);
        temp.completed = (status == "1");

        tasks.push_back(temp);
    }

    file.close();
}
void addTask(vector<Task>& tasks)
{
    Task newTask;

    cout << "Enter task title: ";
    cin.ignore();
    getline(cin, newTask.title);

    newTask.completed = false;

    tasks.push_back(newTask);

    saveTasks(tasks);

    cout << "Task added successfully!\n";
}

void viewTasks(vector<Task>& tasks)
{
    if(tasks.empty())
    {
        cout << "No tasks available.\n";
        return;
    }

    cout << "Task | Status\n";

    for(int i = 0; i < tasks.size(); i++)
    {
        cout << tasks[i].title << " | ";

        if(tasks[i].completed)
            cout << "Completed";
        else
            cout << "Pending";

        cout << endl;
    }
}

void markTaskCompleted(vector<Task>& tasks)
{
    if(tasks.empty())
    {
        cout << "No tasks available.\n";
        return;
    }

    for(int i = 0; i < tasks.size(); i++)
    {
        cout << i + 1 << ". " << tasks[i].title << endl;
    }

    int taskNumber;

    cout << "Enter task number: ";
    cin >> taskNumber;

    if(taskNumber < 1 || taskNumber > tasks.size())
    {
        cout << "Invalid task number.\n";
        return;
    }

    tasks[taskNumber - 1].completed = true;

    saveTasks(tasks);

    cout << "Task marked as completed!\n";
}
int main() {
    vector<Task> tasks;
    int choice;
    loadTasks(tasks);
    while(true) 
    {
        cout << "\n\tTo Do List\n";
        cout << "1. Add Task\n";
        cout << "2. View Tasks\n";
        cout << "3. Mark Task Completed\n";
        cout << "4. Exit\n";
        cout << "Choose option (1-4): ";
        cin >> choice;

        switch(choice)
        {
            case 1:
                addTask(tasks);
                break;

            case 2:
                viewTasks(tasks);
                break;

            case 3:
                markTaskCompleted(tasks);
                break;

            case 4:
                cout << "Exiting program...\n";
                return 0;

            default:
                cout << "Invalid option.\n";
        }
    }
}
