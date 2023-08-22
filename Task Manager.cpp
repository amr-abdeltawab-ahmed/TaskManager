#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include<algorithm>
#include<fstream>
using namespace std;

class Process{
protected:
    string ProcessName;
    string ProcessPID;
    string Memory;
public:
    Process(string name, string pid, string memory){
        ProcessName = name;
        ProcessPID = pid;
        Memory = memory;
    }
    //Getter to get the name
    string get_Name(){
        return ProcessName;
    }
    //Getter to get the PID
    string get_PID(){
        return ProcessPID;
    }
    //Getter to get the Memory
    string get_Memory(){
        return Memory;
    }
};

class TaskManager{
protected:
    vector<Process> plist;
public:
    //Function to add the process
    void addProcess(Process P){
        plist.push_back(P);
    }
    //Function to sort processes by PID
    void sortPID(){
        sort(plist.begin(),plist.end(), [](Process& p1, Process& p2) {return p1.get_PID() < p2.get_PID();});
    }
    //Function to sort processes by name
    void sortName(){
        sort(plist.begin(),plist.end(), [](Process& p1, Process& p2) {return p1.get_Name() < p2.get_Name();});
    }
    //Function to sort processes by memory
    void sortMemory(){
        sort(plist.begin(),plist.end(), [](Process& p1, Process& p2) {return p1.get_Memory() < p2.get_Memory();});
    }
    //Function to print the process
    void print(){
        cout << "Program Name                             PID       MemoryUsage" << endl;
        cout << "=====================================    =====     =======================" << endl;
        for (auto P : plist) {
            cout << left << setw(35) << P.get_Name();
            cout << right << setw(10) << P.get_PID();
            cout << right << setw(30) << P.get_Memory() << 'k' << endl;
        }
    }
    //Function to load the current tasks from cmd
    void load_current_tasks(){
        //write the command in cmd and put it in a file
        system("tasklist > process.txt");
        fstream ProcessList("process.txt");
        string temp, pName, temp_memory, temp_PID;
        plist.clear();

        //ignore first 3 lines
        getline(ProcessList, temp);
        getline(ProcessList, temp);
        getline(ProcessList, temp);


        while(!ProcessList.eof()) {
            getline(ProcessList, temp);

            pName = temp.substr(0,24);
            removeSpaces(pName);
            temp.erase(0, 25);

            temp_PID = temp.substr(0,8);
            removeSpaces(temp_PID);
            temp.erase(0, 34);

            temp_memory = temp.substr(0,6);
            removeSpaces(temp_memory);

            addProcess(Process(pName,temp_PID,temp_memory));
        }


    }
    //Function to Remove the spaces from each string
    void removeSpaces(string str) {
        int count = 0;
        for (int i = 0; str[i]; i++){
            if (str[i] != ' '){
                str[count++] = str[i];
            }
        }
        str[count] = '\0';
    }

};

int main(){
    TaskManager taskmanager;
//    taskmanager.addProcess(Process("Chrome", "5", "10000"));
//    taskmanager.addProcess(Process("NoteBad", "10", "10"));
//    taskmanager.addProcess(Process("PhotoShop", "1", "100"));
//    taskmanager.addProcess(Process("Discord", "15", "1"));
//    taskmanager.addProcess(Process("VSCode", "20", "10000"));

//    cout << "Sorted By Name:" << endl;
//    taskmanager.sortName();
//    taskmanager.print();
//    cout << endl;

//    cout << "Sorted By PID:" << endl;
//    taskmanager.sortPID();
//    taskmanager.print();
//    cout << endl;
//
//    cout << "Sorted By Memory:" << endl;
//    taskmanager.sortMemory();
//    taskmanager.print();
//    cout << endl;

    cout << "----------------------------Current_Tasks------------------------------\n";

    taskmanager.load_current_tasks();
    taskmanager.sortMemory();
    taskmanager.print();
    cout << endl;

    return 0;
}



