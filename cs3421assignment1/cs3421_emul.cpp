#include "memory.h"
#include "clock.h"
#include "cpu.h"

#include <fstream>
#include <cstring>

using namespace std;

int main(int argc, char* argv[])
{
	CPU& cpu = getCPU();

	Memory& mem = getMemory();
	Clock& clock = getClock();

	FILE* infile = fopen(argv[1], "r");
	char* devNameC = new char;
	while (fscanf(infile, "%ms", &devNameC)) {
		string devName(devNameC);

		if (devName == "cpu") {
			cpu.Parse(infile);
		}
		else if (devName == "memory") {
			mem.Parse(infile);
		}
		else {
			clock.Parse(infile);
		}
	}
}