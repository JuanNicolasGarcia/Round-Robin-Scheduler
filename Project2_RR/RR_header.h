#include <string>
#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

class robin {
public:
	void read_file();						// reads the text file
	void load_queue(string, string);		// loads Arrival and Service Times into queue
	void scheduler();						// main scheduling loop
	void calculate_avg();					// get the average TR and wait times
	void write_results();					// write results to output file

	// process node
	struct process {
		int arrival_time;
		double process_time;
		double turnaround_time;
		double wait_time;
		bool been_visited;
	};

private:
	queue<process> item_queue;				// holds the queue for next in line priority
	queue<process> item_list;				// holds the list of processes from the file
	queue<process> results_list;			// holds the final results for evaluation
	double timeQ = 0.5;					// time quantum in milliseconds [50ms, 100ms, 250ms, 500ms]
	int process_count = 0;					// counts how many processes there is in the file
	double context_switch = 0.0;			// time (switching processes) in milliseconds [0ms, 5ms, 10ms, 15ms, 20ms, 25ms]
	double avg_TR_time = 0.0;
	double avg_wait = 0.0;
};

