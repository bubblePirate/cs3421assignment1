#include <fstream>
#include <string>
#include <stdint.h>
#include "clock.h"
#include "cpu.h"

using namespace std;

void Clock::Parse(FILE* infile)
{
	char* commandC;
	fscanf(infile, "%s", &commandC);
	string command(commandC);
	free(commandC);
	if (command == "reset")
		reset();
	else if (command == "tick") {
		int* ticks;
		fscanf(infile, "%d", &ticks);
		tick(*ticks);
		free(ticks);
	}
	else {
		dump();
	}
}

void Clock::reset()
{
	count = 0;
}

void Clock::tick(int numTicks)
{
	CPU& cpu = getCPU();
	for (int i = 0; i < numTicks; i++) {
		cpu.doCpuWork();
	}
}

void Clock::dump()
{
	fprintf(stdout, "%s%d%c", "Clock: ", count, '\n');
}

Clock& getClock()
{
	static Clock clock;
	return clock;
}
