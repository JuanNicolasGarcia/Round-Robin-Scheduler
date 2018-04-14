/*
Name: Juan Nicolas Garcia
Course: Operating Systems (4334)
Assignment: Project 2 - Round Robin simulation
*/

#include "RR_header.h"

int main()
{
	robin RR;

	// loads the text file input into the queue
	RR.read_file();

	// calls the scheduler simulation loop
	RR.scheduler();

	// calculates and displays results
	RR.calculate_avg();

	// writes the results queue to the file
	RR.write_results();

	system("pause");
	return 0;
}