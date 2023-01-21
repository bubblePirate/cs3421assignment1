#include "clock.h"
#include "cpu.h"

using namespace std;

void Clock::Parse(FILE* infile)
{
	char* commandC = new char;
	fscanf(infile, "%s", commandC);
	string command(commandC);
	if (command == "reset")
		reset();
	else if (command == "tick") {
		int* ticks = new int;
		fscanf(infile, "%d", ticks);
		tick(*ticks);
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
