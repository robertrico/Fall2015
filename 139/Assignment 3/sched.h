#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <functional> 
#include <cctype>
#include <locale>

namespace schedular{
	class algorithm;
	class process;

	class algorithm{
		public:
			std::string name;
			int time_quantum;
			int pre_empt;
			static void create_algorithms(std::vector<schedular::algorithm> &algorithms,std::vector<std::string> info_line);
			void RR(std::vector<schedular::process> processes,int time_quantum);
			void SJF(std::vector<schedular::process> processes);
			void PR_noPREMP(std::vector<schedular::process> processes);
			void PR_withPREMP(std::vector<schedular::process> processes);

	};

	class process{
		public:
			int num;
			int arrival_t;
			int burst_len;
			int time_remaining;
			int priority;
			float wait_time;
			int cpu_time;
			static void add_to_processes(std::vector<std::string> process_info,std::vector<schedular::algorithm> &algorithms,std::vector<schedular::process> &processes);
			static void sort_by_arrival(std::vector<schedular::process> &processes);
			static void sort_by_time_remaining(std::vector<schedular::process> &processes);
			static void sort_by_priority(std::vector<schedular::process> &processes);
			static int check_arrivals(std::vector<schedular::process> processes,int time,int cur_process);
	};
}



/* Helper Functions */
static int split(const std::string &txt, std::vector<std::string> &strs, char ch);
static inline std::string &ltrim(std::string &s);
static inline std::string &rtrim(std::string &s);
static inline std::string &trim(std::string &s);
