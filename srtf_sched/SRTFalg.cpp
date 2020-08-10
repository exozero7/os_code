#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

int sum(vector <int> v){

    int sum = 0;
    for(int i = 0; i < v.size(); i++){
        sum += v.at(i);
    }
    
    return sum;
}

int main(){

    ifstream file("data.txt");
    vector <vector <int>> data;

    int id, km, ke;
    while (file >> id){
        vector <int> tmp;
        file >> km;
        file >> ke;
        tmp.push_back(id);
        tmp.push_back(km);
        tmp.push_back(ke);

        data.push_back(tmp);
    }

    cout << "TABLE OF PROCESSES\n";
    cout << "==================\n";

    for(int i = 0; i < data.size(); i++){
        cout << "ID: " << data.at(i).at(0) << "\t";
        cout << "AT: " << data.at(i).at(1) << "\t";
        cout << "ET: " << data.at(i).at(2) << endl;
    }

    file.close();

    vector <vector <int>> conc;
    vector <int> texecleft;

    for(int i = 0; i < data.size(); i++){
        texecleft.push_back(data.at(i).at(2));
    }

    vector <int> wait_time;
    for(int i = 0; i < data.size(); i++){
        wait_time.push_back(0);
    }

    int etime = 0;

    cout << "\nNga\tProcesi\tTek\n";
    bool exe = true;

    int max = -1;
    for(int i = 0; i < data.size(); i++){
        if(data[1][i] > max){
            max = data[1][i];
        }
    }

    while (exe){

        conc.clear();

        for(int i = 0; i < data.size(); i++){
            if(data.at(i).at(1) <= etime && texecleft[i] > 0){
                vector <int> p;
                p.push_back(data[i][0]);
                p.push_back(data[i][1]);
                p.push_back(data[i][2]);
                conc.push_back(p);
            }
        }

        int current_process_execution_time_left = max + 1;

        int current_process_index, current_process_id, current_process_burst_time;

        for(int i = 0; i < conc.size(); i++){

            int index;
            for(int j = 0; j < data.size(); j++){
                if(conc.at(i).at(0) == data.at(j).at(0)){
                    index = j;
                }
            }
            
            if (texecleft.at(index) < current_process_execution_time_left){
                current_process_index = index;
                current_process_id = data.at(index).at(0);
                current_process_burst_time = data.at(index).at(1);
                current_process_execution_time_left = texecleft.at(index);
            }

            else if (texecleft.at(index) == current_process_execution_time_left){
                if(data.at(index).at(1) < current_process_burst_time){
                    current_process_index = index;
                    current_process_id = data.at(index).at(0);
                    current_process_burst_time = data.at(index).at(1);
                    current_process_execution_time_left = texecleft.at(index);
                }
            }
        }

        texecleft[current_process_index] += -1;

        cout << "[" << etime << "]\t" << "[" << current_process_id << "]\t" << "[" << etime+1 << "]" << endl;

        for(int i = 0; i < data.size(); i++){
            if (i == current_process_index or texecleft[i] == 0)
                continue;
            wait_time[i] += 1;
        }
        
        if (sum(texecleft) == 0){
            exe = false;
        }

        etime += 1;
    }

    vector <int> burst_times;
    vector <int> exec_times;
    for (int i = 0; i < data.size(); i++){
        burst_times.push_back(data.at(i).at(1));
        exec_times.push_back(data.at(i).at(2));
    }

    cout << "\n-  WAITING TIME  -" << endl;
    cout << "=================" << endl;
    cout << "Process\tWaiting Time" << endl;

    for(int i = 0; i < data.size(); i++){
        cout << data.at(i).at(0) << "\t" << wait_time.at(i) - data.at(i).at(1) << endl;
    }
    cout << "Average waiting time: " << (sum(wait_time) - sum(burst_times)) / wait_time.size() << endl;

    cout << "\n-  TURN-AROUND TIME  -" << endl;
    cout << "======================" << endl;
    cout << "Process\tTurn-Around time" << endl;
    
    for(int i = 0; i < data.size(); i++){
        cout << data.at(i).at(0) << "\t" << wait_time.at(i) - data.at(i).at(1) + data.at(i).at(2) << endl;
    }
    cout << "\nAverage turn-around time: " << (sum(wait_time) - sum(burst_times)) + sum(exec_times) / wait_time.size() << endl;

    return 0;
}