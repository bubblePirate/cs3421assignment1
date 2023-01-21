#include <fstream>
#include <cstring>
#include <stdint.h>

class CPU 
{
public:
	void Parse(FILE* infile);
	void dump();
	void set(int regNum, uint8_t inByte);
	void reset();

	void doCpuWork();

private:
	uint8_t regs[8];
	uint8_t pc;

	void init();
};

CPU& getCPU();
