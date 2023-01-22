#include <fstream>
#include <cstring>
#include <stdint.h>

class Memory
{
public:
	void Parse(FILE* infile);
	void create(unsigned int size);
	void reset();
	void dump(uint8_t start, uint8_t count);
	void set(uint8_t start, uint8_t count, FILE* infile);

	void startFetch(unsigned int address, unsigned int count, uint8_t* dataPtr, bool* memDonePtr);

private:
	uint8_t* memPtr;
	unsigned int memSize;

};

Memory& getMemory();