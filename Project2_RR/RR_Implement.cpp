#include "RR_header.h"

void robin::read_file()
{
	string temp, temp2;
	ifstream iFile("times.txt");

	if (iFile.is_open())
	{
		while (iFile >> temp)
		{
			iFile >> temp2;
			load_queue(temp, temp2);
			process_count++;
		}
		iFile.close();
	}
	else
	{
		cout << "Unable to open file." << endl;
	}
}

void robin::load_queue(string input1, string input2)
{
	process node;

	// convert string input to int and float and store in node
	node.arrival_time = stoi(input1);
	node.process_time = stod(input2);
	node.turnaround_time = 0.0;				// stores default TA
	node.wait_time = 0.0;					// stores default wait
	node.been_visited = false;				// sets been visited to false

											// add item to the vector
	item_list.push(node);
}

void robin::scheduler()
{
	double counter = 0.0;				// keeps track of cycles completed
	double quant_count = 0.0;				// keeps track of quantum to reset after TQ is reached
	process item = item_list.front();	// sets item to first item in queue

	item_queue.push(item);				// adds first item to list so while loop can start
	item_list.pop();					// removes first item

										// loop will continue until both queue and list are empty
	while (!item_list.empty() || !item_queue.empty())
	{
		// check if item list is not empty don't want to access data not allocated
		if (!item_list.empty())
		{
			// check if next item in list had arrived
			if (item_list.front().arrival_time <= counter)
			{
				// add to queue
				item = item_list.front();
				item_queue.push(item);
				item_list.pop();			// remove from item list				
			}
		}

		// need to check if the item queue is empty first
		// if empty, need to add idle time to counter
		if (item_queue.empty())
		{
			// queue is empty, CPU idle
			counter += 0.001;		// counter keeps going
		}
		else
		{
			// queue is not empty (process next item)
			// process item in queue
			item_queue.front().process_time -= 0.001;			// decrement process time by 1 cycle (1ms)

																// checks if the process has had CPU time before
			if (item_queue.front().been_visited == false)
			{
				item_queue.front().been_visited = true;	// sets flag
				item_queue.front().wait_time = counter - item_queue.front().arrival_time;	// sets the wait (when item is first processed vs arrival time)
				avg_wait += item_queue.front().wait_time;
			}

			// increment the counters
			quant_count += 0.001;			// add 1ms
			counter += 0.001;				// add 1ms

											// check if process has finished
			if (item_queue.front().process_time <= 0.0)
			{
				item_queue.front().turnaround_time = counter - item_queue.front().arrival_time;		// calculate turnaround time
				avg_TR_time += item_queue.front().turnaround_time;
				results_list.push(item_queue.front());												// finished process, add to results list
				item_queue.pop();																	// remove item from queue (finished processing)
				quant_count = 0.0;																	// reset quantum counter
				counter += context_switch;															// changing process, so add context switch time to counter
			}
			else if (fabs(quant_count - timeQ) < 1.0e-7)
			{
				// process has used enough time
				item = item_queue.front();	// set object to first item on queue list
				item_queue.pop();			// remove first item
				item_queue.push(item);		// move to back of queue
				quant_count = 0;			// reset quantum counter
				counter += context_switch;	// changing process, so add context switch time to counter
			}
		}
	}
}

void robin::calculate_avg()
{
	avg_TR_time = avg_TR_time / process_count;
	avg_wait = avg_wait / process_count;

	cout << "Results for TQ: " << timeQ << " and CS: " << context_switch << endl;
	cout << "Average Turnaround Time: " << avg_TR_time << endl;
	cout << "Average Wait Time: " << avg_wait << endl;
}

void robin::write_results()
{
	ofstream results_file;
	results_file.open("results.txt");
	if (results_file.is_open())
	{
		while (!results_list.empty())
		{
			results_file << results_list.front().arrival_time << " ";
			results_file << results_list.front().process_time << " ";
			results_file << results_list.front().turnaround_time << " ";
			results_file << results_list.front().wait_time << endl;
			results_list.pop();
		}
	}
	else
	{
		cout << "Could not write to results file" << endl;
	}

	results_file.close();
}