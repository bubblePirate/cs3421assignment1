#include "cpu.h"
#include "memory.h"

using namespace std;

void CPU::Parse(FILE* infile)
{
	char* commandC;
	fscanf(infile, "%s", &commandC);
	string command(commandC);
	free(commandC);
	if (command == "dump")
		dump();
	else if (command == "set") {
		fscanf(infile, "%s", &commandC);
		char* regChar;
		fscanf(infile, "%c", &regChar); //scans in R
		fscanf(infile, "%c", &regChar);
		int reg = *regChar - 'A';
		uint8_t* inByte;
		fscanf(infile, "%x", &inByte);
		set(reg, *inByte);
	}
	else {
		reset();
	}

}

void CPU::dump()
{
	fprintf(stdout, "%s%X%c", "PC: 0x", pc, '\n');
	for (int i = 0; i < 8; i++) {
		char regChar = 'A';
		fprintf(stdout, "%c%c%s%X%c", 'R', regChar, ": 0x", regs[i], '\n');
		regChar++;
	}
}

void CPU::set(int regNum, uint8_t setByte)
{
	regs[regNum] = setByte;
}

void CPU::reset()
{
	for (int i = 0; i < 8; i++) {
		regs[i] = 0;
	}
	pc = 0;
}

void CPU::doCpuWork()
{
	//move registers
	for (int i = 7; i > 0; i--) {
		regs[i-1] = regs[i];
	}
	//read memory
	Memory& mem = getMemory();
	uint8_t fetchByte;
	bool fetchDone;
	mem.startFetch(pc, 1, &fetchByte, &fetchDone);
	//store in r0
	regs[0] = fetchByte;
	//increment pc
	pc++;
}

void CPU::init()
{
	for (int i = 0; i < 8; i++) {
		regs[i] = 0;
	}
	pc = 0;
}

CPU& getCPU()
{
	static CPU cpu;
	return cpu;
}
