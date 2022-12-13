//
//  Q2.hpp
//  WEEK 10
//
//  Created by Sayan Jain on 11/28/22.
//

#ifndef Q2_hpp
#define Q2_hpp

#include <stdio.h>
#include <cstdlib>
#include <cassert>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

vector<string> names = {"Colin Small","Ross Padilla","Amani Fritz","Leroy Arnold","Andreas Pratt","Madilyn Mays","Amiya Oliver","Immanuel Berg","Bryan Moore","Alexis Terry","Tiara Yoder","Lucas Hays","Arturo Fitzpatrick","Travis Harrell","Evelin Glover","Kaylee Beltran","Cassie Barnett","Yuliana Zhang","Shania Bass","Todd Fitzgerald","Rudy Cunningham","Kai Ware","Soren Wong","Leonel Marks","Greta Rojas","Skylar Carr","Emiliano Stokes","Kennedy Marshall","Trinity Carter","Chance Gardner"};


vector<string> topics = {"stacks","queues","binary trees","b-trees","sorting","searching","maps"};

namespace officeHours {
    class averager{
    public:
        // CONSTRUCTOR
        averager( );
        // MODIFICATION function
        void next_number(double value);
        // CONSTANT functions
        int how_many_numbers( ) const { return count; }
        double getSum(){return sum;}
        double average( ) const;
    private:
        int count; // How many numbers have been given to the averager
        double sum;   // Sum of all the numbers given to the averager
    };

    class Student{
    public:
        // CONSTRUCTOR
        Student(int arrivalTime, int serviceTime, int priorityLevel, string _name, string _subject, int arrivalDay_);
        Student(string _name, int days);
        // MODIFICATION functions
        void one_minute( );
        void start_helping( );
        // CONSTANT function
        bool is_busy( ) const { return (help_time_left > 0); }
        // getters
        int getArrivalTime(){return arrivalTime;}
        int getServiceTime(){return seconds_for_help;}
        int getHelpTimeLeft(){return help_time_left;}
        int getPriorityLevel(){return priority;}
        int getDaysInOH(){return days_in_OH;}
        string getName(){return name;}
        string getSubject(){return subject;}
        int getArrivalDay(){return arrivalDay;}
        
    private:
        int arrivalTime;
        int seconds_for_help; // Seconds to help a student
        int help_time_left;   // Seconds until prev student no longer busy
        int priority;
        string name;
        string subject;
        int days_in_OH;
        int arrivalDay;
    };

    class DayData{
    private:
        double avgWaitTime;
        double professorOvertime;
        double avgTimeHelped;
        double studentsHelped;
        multimap<string,Student> map;
    public:
        DayData(double w, double x, double y, double z, multimap<string,Student> _map);
        double getAvgWaitTime(){return avgWaitTime;}
        double getprofessorOvertime(){return professorOvertime;}
        double getavgTimeHelped(){return avgTimeHelped;}
        double getStudentsHelped(){return studentsHelped;}
        multimap<string,Student> getMap(){return map;}
    };

    bool operator ==(Student a,Student b){
        return((a.getName() == b.getName()) && (a.getSubject() == b.getSubject()) && (a.getArrivalDay()==b.getArrivalDay()));
    }

    bool operator <(Student a, Student b){
        return (a.getPriorityLevel()<b.getPriorityLevel());
    }

    bool operator >(Student a, Student b){
        return (a.getDaysInOH()>b.getDaysInOH());
    }

    averager::averager( ){
        count = 0;
        sum = 0;
    }

    void averager::next_number(double value){
        ++count;
        sum += value;
    }

    double averager::average( ) const{
    // Library facilities used: cassert
        if(how_many_numbers( ) > 0){
            return sum/count;
        }
        return 0;
    }

    Student::Student(int arrivalTime_, int serviceTime, int priorityLevel, string _name, string _subject, int arrivalDay_){
        seconds_for_help = serviceTime;
        arrivalTime = arrivalTime_;
        help_time_left =0;
        priority = priorityLevel;
        name = _name;
        subject = _subject;
        arrivalDay = arrivalDay_;
    }

    Student::Student(string _name, int days){
        name = _name;
        days_in_OH = days;
    }

    void Student::one_minute( ){
        if (is_busy()){
            --help_time_left;
        }
    }

    void Student::start_helping(){
        if(!is_busy()){
            help_time_left = seconds_for_help;
        }
    }

    DayData::DayData(double w, double x, double y, double z, multimap<string,Student> _map){
        studentsHelped = w;
        avgWaitTime = x;
        avgTimeHelped = y;
        professorOvertime = z;
        map = _map;
    }
}

#endif /* Q2_hpp */
