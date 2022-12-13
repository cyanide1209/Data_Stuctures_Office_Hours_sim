//
//  Q2.cpp
//  WEEK 10
//
//  Created by Sayan Jain on 11/28/22.
//

#include "Q2.hpp"
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <vector>
#include <queue>
#include <map>

using namespace std;
using namespace officeHours;

//this does not have a searching within it, but seems ez enuf to implement :)

vector<int> random_arrival(int n){
    vector<int> arrivals;
    for(int i = 0; i<n;++i){
        int arrival = rand() % (60)+1;
        //random number between 1 and 60 for arrival time
        arrivals.push_back(arrival);
    }
    return arrivals;
}

queue<int> sort_arrivals(vector<int> arrivals){
    queue<int> q;
    for(int i = 0; i<arrivals.size();++i){
        for(int j = 0; j<arrivals.size()-1;++j){
            if(arrivals[j] > arrivals[j+1]){
                int temp = arrivals[j+1];
                arrivals[j+1] = arrivals[j];
                arrivals[j] = temp;
            }
        }
    }
    for(int i = 0; i<arrivals.size(); ++i){
        q.push(arrivals[i]);
    }
    return q;
}

queue<int> service_time(int x){
    queue<int> service_times;
    for(int i = 0; i<x; ++i){
        service_times.push((rand() % 30) +1);
        //students assigned a random number between 1 and 30 for amount of help needed
    }
    return service_times;
}

vector<string> setNames(vector<string> x){
    for(int i = 0;i<names.size();i++){
        x.push_back(names[i]);
    }
    return x;
}

DayData office_hours_simulation(multimap<string,Student> map, int arrivalDay){
    int numOfStudents = (rand() % 11);
//random number between 0 and 10 for amount of students that show up to office hours
    int total_time = 60;
    priority_queue<Student> students;
    Student test(0,300,0,"","",arrivalDay);
    averager wait_times;
    averager help_times;
    vector<string> x;
    x = setNames(x);
    vector<int> arrivalTimes = random_arrival(numOfStudents);
    queue<int> arrivalOrder = sort_arrivals(arrivalTimes);
    queue<int> serviceTimes = service_time(arrivalTimes.size());
    int current_minute;
    for(current_minute = 1; current_minute<=total_time; ++current_minute){
        if(numOfStudents == 0){
            DayData d(0,0,0,0,map);
            return d;
        }
        while((arrivalOrder.front() == current_minute)&&(!arrivalOrder.empty())){
            int z = rand() % x.size();
            Student temp(current_minute, serviceTimes.front(), (rand() % 3 +1), x[z], topics[rand()%7],arrivalDay);
            x.erase(x.begin()+z);
            map.insert(pair<string,Student>(temp.getName(),temp));
            serviceTimes.pop();
            arrivalOrder.pop();
            students.push(temp);
         }
         if((!students.empty()) && (!test.is_busy())){
            test = students.top();
            students.pop();
            wait_times.next_number(current_minute-test.getArrivalTime());
            help_times.next_number(test.getServiceTime());
            test.start_helping();
         }
         if((current_minute == total_time) && (!students.empty() || test.is_busy())){
            total_time += test.getHelpTimeLeft();
         }
         test.one_minute();
    }
    DayData d(wait_times.how_many_numbers(),wait_times.average(),help_times.average(),(total_time-60),map);
//    cout<<"The professor helped "<<d.getStudentsHelped()<<" students today"<<endl;
//    cout<<"On average, each student waited "<<d.getAvgWaitTime()<<" minutes"<<endl;
//    cout<<"On average, each student spent "<<d.getavgTimeHelped()<<" minutes with the professor"<<endl;
//    cout<<"The professor spent "<<d.getprofessorOvertime()<<" minutes of overtime today"<<endl;
    return d;
}

void searchSubjectData(multimap<string,Student> map, string subject){
    cout<<"Students that asked questions about "<<subject<<":"<<endl;
    cout<<"    Name            Office Hours Day"<<endl;
    int i=0;
    for (auto itr = map.begin(); itr != map.end(); itr++){
        if(itr->second.getSubject()==subject){
            cout<<itr->first<<"---------------"<<itr->second.getArrivalDay()<<endl;
            i++;
        }
    }
    cout<<"Students came to office hours to study "<<subject<<" a total of "<<i<<" times"<<endl;
}

void outputMapData(multimap<string,Student> map){
//    multimap<string, string>::iterator itr;
    cout<<endl;
    cout<<endl;
    cout<<"100 Day Sudent Summary:"<<endl;
    int x;
    int y;
    vector<Student> v;
    //order by number of times each student showed up
    //psedocode:
    //overload > operator so that it only compares times they showed up to OH
    //create array of new object and put all students in that
    //order the array
    //print
//    for(int i = 0;i<30;i++){
//        x=0;
//        for(int j = 0;j<7;j++){
//            y=0;
//            //this is rly inefficient lol
//            for (auto itr = map.begin(); itr != map.end(); itr++){
//                if(itr->first==names[i] && itr->second==topics[j]){
//                    y++;
//                }
//            }
//            if(j==0){
//                cout<<names[i]<<endl;
//            }
//            cout<<"    "<<topics[j]<<"--"<<y<<" times"<<endl;;
//            x+=y;
//        }
//        cout<<"    Total: "<<x<<" times "<<endl;
//        //make vector of students w only names and days in OH
//        Student temp(names[i],x);
//        v.push_back(temp);
//    }
    
    //map prints by going through the map in order and printing as we go 
    int stacks=0,queues=0,binary_trees=0,b_trees=0,sorting=0,searching=0,maps=0,total=0;
    string name = map.begin()->first;
    for (auto itr = map.begin(); itr != map.end(); itr++){
        if(itr->first != name){
            cout<<"    stacks--"<<stacks<<" times"<<endl;
            cout<<"    queues--"<<queues<<" times"<<endl;
            cout<<"    binary trees--"<<binary_trees<<" times"<<endl;
            cout<<"    b-trees--"<<b_trees<<" times"<<endl;
            cout<<"    sorting--"<<sorting<<" times"<<endl;
            cout<<"    searching--"<<searching<<" times"<<endl;
            cout<<"    maps--"<<maps<<" times"<<endl;
            cout<<"    Total:"<<total<<" times"<<endl;
            Student temp(name,total);
            v.push_back(temp);
            stacks = 0;
            queues = 0;
            binary_trees = 0;
            b_trees = 0;
            sorting = 0;
            searching = 0;
            maps = 0;
            total = 0;
            name = itr->first;
        }
        if(total==0){
            cout<<itr->first<<endl;
        }
        if(itr->second.getSubject()=="stacks"){
            stacks++;
        }
        else if(itr->second.getSubject()=="queues"){
            queues++;
        }
        else if(itr->second.getSubject()=="binary trees"){
            binary_trees++;
        }
        else if(itr->second.getSubject()=="b-trees"){
            b_trees++;
        }
        else if(itr->second.getSubject()=="sorting"){
            sorting++;
        }
        else if(itr->second.getSubject()=="searching"){
            searching++;
        }
        else if(itr->second.getSubject()=="maps"){
            maps++;
        }
        total++;
    }
    //print last person
    cout<<"    stacks--"<<stacks<<" times"<<endl;
    cout<<"    queues--"<<queues<<" times"<<endl;
    cout<<"    binary trees--"<<binary_trees<<" times"<<endl;
    cout<<"    b-trees--"<<b_trees<<" times"<<endl;
    cout<<"    sorting--"<<sorting<<" times"<<endl;
    cout<<"    searching--"<<searching<<" times"<<endl;
    cout<<"    maps--"<<maps<<" times"<<endl;
    cout<<"    Total: "<<total<<" times"<<endl;
    Student temp(name,total);
    v.push_back(temp);
    

    //insertion sort v by days in OH
    int i = 0;
    int j = 0;
    for(;i<v.size();i++){
        j=i;
        while(v[j].getDaysInOH()<v[j-1].getDaysInOH()){
            Student temp = v[j-1];
            v[j-1] = v[j];
            v[j] = temp;
            j--;
        }
    }
    
    //print vector(now an ordered list of students)
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<"Students ordered by the amount of days they attended office hours:"<<endl;
    cout<<endl;
    cout<<endl;
    for(int i = 0;i<v.size();i++){
        cout<<v[i].getName()<<"---"<<v[i].getDaysInOH()<<" times"<<endl;
    }
    
    
    //search through map and for chosen subject print student name and arrival day
    cout<<endl;
    cout<<endl;
    cout<<endl;
    searchSubjectData(map, topics[3]);
    cout<<endl;
}
    
//RULES:
//max of 30 students can show up to office hours
//30 students in the class
//every student can show up to office hours once
int main(){
    multimap<string,Student> map;
    averager numStudents;
    averager wait_times;
    averager help_times;
    averager professorOvertime;
    int day = 1;
    for(day = 0; day < 100; ++day){
//        cout<<day<<endl;
        DayData temp = office_hours_simulation(map, day+1);
        map = temp.getMap();
        numStudents.next_number(temp.getStudentsHelped());
        wait_times.next_number(temp.getAvgWaitTime());
        help_times.next_number(temp.getavgTimeHelped());
        professorOvertime.next_number(temp.getprofessorOvertime());
    }
    cout<<"Over "<< day <<" days, the professor helped "<<numStudents.getSum()<<" students"<<endl;
    cout<<"Over "<< day <<" days, each student waited an average of "<<wait_times.average()<<" minutes"<<endl;
    cout<<"Over "<< day <<" days, the professor spent an average of "<<help_times.average()<<" minutes with each student"<<endl;
    cout<<"Over "<< day <<" days, the professor spent an average of "<<professorOvertime.average()<<" minutes of overtime per day"<<endl;
    outputMapData(map);
}
