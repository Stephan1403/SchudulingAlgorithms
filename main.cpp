#include <stdio.h>
#include <iostream>

// Container
#include <vector>
#include <queue>
#include <set>
#include <algorithm>            // For min

//#include "Process.h"
//#include "QueueFactory.h"
#include "Scheduler.h"


/*---------------- Process Strategies ----------------*/



/*

// Shortest job first but with ready times
double SJF_r_times_avg(std::vector<Process> p_vec){
    int total_time = 0;
    int current_time = 0;
    int done_processes = 0;
    
    // Create queue
    std::queue<Process> p_queue;
    Queue_Creator qc(&p_queue, p_vec, SJF);

    qc.update_queue(current_time, true);             
    current_time++;
    Process p = p_queue.front();                 // Load first process

    while(done_processes < p_vec.size()){
        qc.update_queue(current_time, true);     // Load new processes (if available)
        p = p_queue.front();                     // Always take process from front

        if(p.is_completed()){
            p_queue.pop();                      // remove process from queue
            total_time += current_time;
            done_processes++;
        }

        p.give_p_time(1);                       // Give 1 intervall time
        current_time++;
    }

    return total_time / double(p_vec.size());
}

*/

/*


// Earliest deadline first
double EDF_avg(std::vector<Process> p_vec){
    int total_time = 0;
    int current_time = 0; 

    // Create queue
    std::queue<Process> p_queue;
    Queue_Creator qc(&p_queue, p_vec, EDF);
    qc.update_queue(0, false);

    while(!p_queue.empty()){
        Process p = p_queue.front();
        p_queue.pop();

        current_time += p.get_e_time();
        total_time += current_time; 
    }
     
    return total_time / double(p_vec.size());

}

// TODO: deadline 


// Least Laxity First - (deadline - ready_time - execution time)
double LLF_avg(std::vector<Process> p_vec){
    int total_time = 0;
    int current_time = 0; 

    // Create queue
    std::queue<Process> p_queue;
    Queue_Creator qc(&p_queue, p_vec, LLF);
    qc.update_queue(0, false);

    while(!p_queue.empty()){
        Process p = p_queue.front();
        p_queue.pop();

        current_time += p.get_e_time();
        total_time += current_time; 
    }

    return total_time / double(p_vec.size());
}


// Round Robin
double RR_avg(std::vector<Process> p_vec, int q){

    int total_time = 0;
    int current_time = 0; 

    // Create queue
    std::queue<Process> p_queue;
    Queue_Creator qc(&p_queue, p_vec, RR);
    qc.update_queue(0, false);

    while(!p_queue.empty()){

        Process p = p_queue.front();
        int r_time = p.give_p_time(q);  // Give p cpu time and return the rest time that the process didn't need
        current_time += (q - r_time);   // update current time (intervall - that the process didn't need)
        p_queue.pop();                  // Give cpu to other process

        // Check if process is complted
        if(p.is_completed())
            total_time += current_time; 
        else  // Process needs more cpu time, put at end of queue
            p_queue.push(p);
    }

    return total_time / double(p_vec.size());
}

*/





/*---------------- Process Strategies ----------------*/

double FCFS_avg(std::vector<Process*> p_vec){ 
    double total_time = 0; 
    double current_time = 0;

    // Create scheduler
    Scheduler S(p_vec, FCFS);
    S.update_p_queue(0);
    Process* p;

    while((p = S.next_job()) != nullptr){

        current_time += p->get_e_time();
        total_time += current_time;

        p->set_completed();
    }
    std::cout << "FCFS average: " << total_time / S.get_job_counter() << std::endl;

    return total_time / S.get_job_counter();
}



double SJF_avg(std::vector<Process*> p_vec){
    double total_time = 0;
    double current_time = 0;
    
    // Create scheduler
    Scheduler S(p_vec, SJF);
    S.update_p_queue(0);
    Process* p;

    while((p = S.next_job()) != nullptr){

        current_time += p->get_e_time();
        total_time += current_time;

        p->set_completed();
    }

    std::cout << "SJF average: " << total_time / S.get_job_counter() << std::endl;

    return total_time / S.get_job_counter();
}



double EDF_avg(std::vector<Process*> p_vec){
    double total_time = 0;
    double current_time = 0;
    
    // Create scheduler
    Scheduler S(p_vec, EDF);
    S.update_p_queue(0);
    Process* p;

    while((p = S.next_job()) != nullptr){

        current_time += p->get_e_time();
        total_time += current_time;

        p->set_completed();
    }

    std::cout << "SJF average: " << total_time / S.get_job_counter() << std::endl;

    return total_time / S.get_job_counter();

}




double LLF_avg(std::vector<Process*> p_vec){
    double total_time = 0;
    double current_time = 0;
    
    // Create scheduler
    Scheduler S(p_vec, LLF);
    S.update_p_queue(0);
    Process* p;

    while((p = S.next_job()) != nullptr){

        current_time += p->get_e_time();
        total_time += current_time;

        p->set_completed();
    }

    std::cout << "LLF average: " << total_time / S.get_job_counter() << std::endl;

    return total_time / S.get_job_counter();
}




/*---------------- Main & initalization ----------------*/

void create_processes(std::vector<Process*> &vec){

    vec.push_back(new Process(1, 8, 0, 10) );
    vec.push_back(new Process(2, 5, 0, 9) );
    vec.push_back(new Process(3, 4, 0, 9) );


}




int main(){

    // Create vector with processes 
    //std::vector<Process*> p_vector = create_p_vector();

    // Create processes
    std::vector<Process*> p_vector;

    // Call functions
    create_processes(p_vector);                                     // Reset processes
    FCFS_avg(p_vector);

    create_processes(p_vector);                                             
    SJF_avg(p_vector);

    create_processes(p_vector);
    EDF_avg(p_vector);

    create_processes(p_vector);
    LLF_avg(p_vector);

    create_processes(p_vector);
    LLF_avg(p_vector);


    /*
    std::cout << "SJF average: " << SJF_default_avg(p_vector) << std::endl;
    std::cout << "EDF average: " << EDF_avg(p_vector) << std::endl; 
    std::cout << "LLF average: " << LLF_avg(p_vector) << std::endl; 
    std::cout << "RR average: " << RR_avg(p_vector, 3) << std::endl; 
    */   
}