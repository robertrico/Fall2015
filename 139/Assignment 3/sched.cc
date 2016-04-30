#include "sched.h"


int main(int argc, char *args[])
{
    std::ifstream is("input.txt");
    std::vector<std::string> str_arr;
	std::vector<schedular::process> processes;
	std::vector<schedular::algorithm> algorithms;

	std::string str;

    while(std::getline(is, str)) {
        str_arr.push_back(str);
    }

	/* Build Virtual Priority queue of system processes */
	schedular::process::add_to_processes(str_arr,algorithms,processes);
	schedular::process::sort_by_arrival(processes);

	std::ofstream outfile;
	outfile.open("output.txt", std::ios_base::app);
	/* Run Each Algorithm on the input data */
	for(std::vector<schedular::algorithm>::iterator it = algorithms.begin(); it != algorithms.end(); ++it) {
		if(it->name.compare("RR") == 0){
			outfile << "#### Executing RR ####" << std::endl; 
			it->RR(processes,it->time_quantum);
			outfile << std::endl; 
		}
		if(it->name.compare("SJF") == 0){
			outfile << "#### Executing SJF ####" << std::endl; 
			it->SJF(processes);
			outfile << std::endl; 
		}
		if(it->name.compare("PR_noPREMP") == 0){
			outfile << "#### Executing PR_noPREMPT #####" << std::endl; 
			it->PR_noPREMP(processes);
			outfile << std::endl; 
		}
		if(it->name.compare("PR_withPREMP") == 0){
			outfile << "#### Executing PR_withPREMPT ####" << std::endl; 
			it->PR_withPREMP(processes);
			outfile << std::endl; 
		}
	}

    return 0;
}

void schedular::algorithm::RR(std::vector<schedular::process> processes,int time_quantum)
{
	int time=0,j=0, process_count = processes.size();
	float avg = 0.00;
	std::ofstream outfile;
	outfile.open("output.txt", std::ios_base::app);

	/* Cycle Through System Processes, but ignore those that have not arrived */
	/* Ignoring = Process has not arrived */
	while(1){
		if(processes.size() == 0)
			break;

		/* Simulate Process Arrival by Checking Current System Processes and arrival times */
		/* If they have arrived, give them the CPU and execute the burst length */
		/* Then remove it from the proceeses virtual priority queue */
		if(processes[j].arrival_t <= time && processes[j].time_remaining > 0){

			outfile << "Time " << time << " Process " << processes[j].num <<  std::endl; 

			/* Apply the time quantum to the process to decrease its needed running time */
			if(processes[j].time_remaining <= time_quantum){
				time = time + processes[j].time_remaining;
				processes[j].cpu_time += processes[j].time_remaining; 
				processes[j].time_remaining = 0; 
			}else{
				processes[j].time_remaining -= time_quantum; 
				processes[j].cpu_time += time_quantum; 
				time = time + time_quantum;
			}

			/* If process is finished */
			if(processes[j].time_remaining <= 0){
				avg += time-processes[j].cpu_time-processes[j].arrival_t;
				processes.erase(processes.begin() + j);
				continue;
			}
		}

		/* If No System Processes Exist Leave Algorithm */
		if(processes.size() == 0)
			break;

		/* Check the next process in the system */
		/* No time has passed if process has not arrived */
		j = (j+1) % processes.size();
	}

	outfile << "Average Waiting time is " << avg / process_count << std::endl; 

	return;
}

void schedular::algorithm::SJF(std::vector<schedular::process> processes)
{
	int time=0,j=0, process_count = processes.size();
	float avg = 0.00;
	std::ofstream outfile;
	outfile.open("output.txt", std::ios_base::app);

	schedular::process::sort_by_time_remaining(processes);
	while(1){
		schedular::process::sort_by_time_remaining(processes);

		if(processes.size() == 0)
			break;

		/* If process has not arrived ignore it */
		if(processes[j].arrival_t <= time && processes[j].time_remaining > 0){

			outfile << "Time " << time << " Process " << processes[j].num <<  std::endl; 

			processes[j].wait_time = time - processes[j].wait_time;

			/* No Premeption, advance time by time_remaining and remove */
			time = time + processes[j].time_remaining;
			processes[j].time_remaining = 0; 

			avg += processes[j].wait_time-processes[j].arrival_t;
			processes.erase(processes.begin() + j);
			schedular::process::sort_by_time_remaining(processes);
			j = 0;
			continue;
			
		}else{
			/* No time has passed if process has not arrived */
			j = (j+1) % processes.size();
		}

		if(processes.size() == 0)
			break;
	}

	outfile << "Average Waiting time is " << avg / process_count << std::endl; 

	return;
}

/* Similar to job first, however sorting happens once */
void schedular::algorithm::PR_noPREMP(std::vector<schedular::process> processes)
{
	int time=0,j=0, process_count = processes.size();
	float avg = 0.00;

	std::ofstream outfile;
	outfile.open("output.txt", std::ios_base::app);

	schedular::process::sort_by_priority(processes);
	while(1){

		if(processes.size() == 0)
			break;

		outfile << "Time " << time << " Process " << processes[j].num <<  std::endl; 

		/* If process has not arrived ignore it */
		if(processes[j].arrival_t <= time && processes[j].time_remaining > 0){

			processes[j].wait_time = time - processes[j].wait_time;

			/* No preemtion, process is removed from virtual priority queue */
			time = time + processes[j].time_remaining;
			avg += processes[j].wait_time-processes[j].arrival_t;
			processes.erase(processes.begin() + j);
			j = 0;
			continue;

		}else{
			/* No time has passed if process has not arrived */
			j = (j+1) % processes.size();
		}

		if(processes.size() == 0)
			break;
	}

	outfile << "Average Waiting time is " << avg / process_count << std::endl; 

	return;
}

void schedular::algorithm::PR_withPREMP(std::vector<schedular::process> processes)
{
	int time=0,j=0, process_count = processes.size(),last_cpu = 0;
	float avg = 0.00;

	std::ofstream outfile;
	outfile.open("output.txt", std::ios_base::app);

	schedular::process::sort_by_priority(processes);
	while(1){
		if(processes.size() == 0)
			break;

		/* Ignore processes that have not arrived */
		if(processes[j].arrival_t <= time && processes[j].time_remaining > 0){

			if(!last_cpu){
				outfile << "Time " << time << " Process " << processes[j].num <<  std::endl; 
			}

			processes[j].wait_time = time - processes[j].wait_time;

			time++;
			processes[j].cpu_time++;
			processes[j].time_remaining--;

			if(processes[j].time_remaining <= 0){
				avg += time-processes[j].cpu_time-processes[j].arrival_t;
				processes.erase(processes.begin() + j);
				j = 0;
				last_cpu = 0;
				continue;
			}

			/* If a processes has arrived, pre empt*/
			int k = schedular::process::check_arrivals(processes,time,j);
			if(k == j){
				last_cpu = 1;
				continue;
			}else{
				last_cpu = 0;
				j = k;
			}

		}else{
			/* No time has passed if process has not arrived */
			j = (j+1) % processes.size();
		}

		if(processes.size() == 0)
			break;
	}

	outfile << "Average Waiting time is " << avg / process_count << std::endl; 

	return;
}
/* Build Virtual Priority Queue for System from File */
/* If a condition is not met when traversing the vector, move to next object */
void schedular::process::add_to_processes(std::vector<std::string> process_info,std::vector<schedular::algorithm> &algorithms,std::vector<schedular::process> &processes)
{
	int line_num = 1;
	for(std::vector<std::string>::iterator it = process_info.begin(); it != process_info.end(); ++it) {

		std::vector<std::string> proc_info;
		split(*it, proc_info, ' ' );
		schedular::process cur;

		/* Algorithm Information */
		if(line_num == 1){
			schedular::algorithm::create_algorithms(algorithms,proc_info);
			line_num++;
			continue;
		}

		/* Process Count */
		if(line_num == 2){
			std::istringstream str_int(proc_info[0]);

			line_num++;
			continue;
		}

		/* Create and Add Process to Vector from info */
		/* This Vectore simulates the system and its processes */
		std::istringstream str_int;

		int i,j=0;

		for(i=0;i < 4; i++){
			str_int.str(proc_info[i]);
			switch(i){
				case 0:
					str_int >> cur.num;
					break;
				case 1:
					str_int >> cur.arrival_t;
					break;
				case 2:
					str_int >> cur.burst_len;
					j = cur.burst_len;
					break;
				case 3:
					str_int >> cur.priority;
					break;
			}
			str_int.str("");
			str_int.clear();
		}

		cur.time_remaining = j;
		cur.wait_time = 0;
		cur.cpu_time = 0;

		processes.push_back(cur);
		line_num++;
	}
}

/* Create Vector of Algorithms to run tests with */
void schedular::algorithm::create_algorithms(std::vector<schedular::algorithm> &algorithms,std::vector<std::string> info_line)
{
	int param = 0;
	for(std::vector<std::string>::iterator it = info_line.begin(); it != info_line.end(); ++it) {
		schedular::algorithm algorithm;
		std::string tmp(*it);
		tmp = trim(tmp);
		if(tmp.compare("RR") == 0){
			algorithm.name = tmp;
			++it;
			tmp = *it;
			std::istringstream str_int(tmp);
			str_int >> algorithm.time_quantum;
			algorithms.push_back(algorithm);
			continue;
		}
		algorithm.time_quantum = 0;
		algorithm.name = tmp;
		algorithms.push_back(algorithm);
		param++;
	}
}

/* Check for a higher priority process that has arrived */
int schedular::process::check_arrivals(std::vector<schedular::process> processes,int time,int cur_process)
{
	int highest = cur_process;
	for(std::vector<schedular::process>::iterator it = processes.begin(); it != processes.end(); ++it) {
		if(it->arrival_t <= time && it->priority < processes[cur_process].priority && it->time_remaining > 0)
			highest = it - processes.begin();
	}
	return highest;
}

/* Sort System Processes by time remaining to exit */
void schedular::process::sort_by_time_remaining(std::vector<schedular::process> &processes)
{
	unsigned int j=0,first=0;
	std::vector<schedular::process> reorder;
	
	while(1){
		if(processes[j].time_remaining < processes[first].time_remaining){
			first = j; 
		}

		if(j == processes.size()-1){
			reorder.push_back(processes[first]);
			processes.erase(processes.begin()+(first));
			first = 0;
		}

		if(processes.size() == 0)
			break;

		j = (j+1) % processes.size();
	}
	processes = reorder;
}

/* Sort System Processes by arrival time */
void schedular::process::sort_by_arrival(std::vector<schedular::process> &processes)
{
	unsigned int j=0,first=0;
	std::vector<schedular::process> reorder;
	
	while(1){
		if(processes[j].arrival_t < processes[first].arrival_t){
			first = j; 
		}

		if(j == processes.size()-1){
			reorder.push_back(processes[first]);
			processes.erase(processes.begin()+(first));
			first = 0;
		}

		if(processes.size() == 0)
			break;

		j = (j+1) % processes.size();
	}
	processes = reorder;
}

/* Sort System Processes by priority */
void schedular::process::sort_by_priority(std::vector<schedular::process> &processes)
{
	unsigned int j=0,first=0;
	std::vector<schedular::process> reorder;
	
	while(1){
		if(processes[j].priority < processes[first].priority){
			first = j; 
		}

		if(j == processes.size()-1){
			reorder.push_back(processes[first]);
			processes.erase(processes.begin()+(first));
			first = 0;
		}

		if(processes.size() == 0)
			break;

		j = (j+1) % processes.size();
	}
	processes = reorder;
}

/* Helper functions */
int split(const std::string &str, std::vector<std::string> &strs, char character)
{
    unsigned int found = str.find( character );
    unsigned int position = 0;
    strs.clear();

    // split 
    while( found != std::string::npos ) {
        strs.push_back( str.substr( position, found - position + 1 ) );
        position = found + 1;

        found = str.find( character, position );
    }

    // Get last element
    strs.push_back( str.substr( position, std::min( found, str.size() ) - position + 1 ) );

    return strs.size();
}

// trim from start
inline std::string &ltrim(std::string &s) 
{
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
        return s;
}

// trim from end
inline std::string &rtrim(std::string &s) 
{
        s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
        return s;
}

// trim from both ends
inline std::string &trim(std::string &s) 
{
        return ltrim(rtrim(s));
}
