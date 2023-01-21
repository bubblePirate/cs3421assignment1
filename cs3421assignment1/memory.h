#include <fstream>
#include <string>
#include <stdint.h>

class Memory
{
public:
	void Parse(FILE* infile);
	void create(uint8_t size);
	void reset();
	void dump(uint8_t start, uint8_t count);
	void set(uint8_t start, uint8_t count, FILE* infile);

	void startFetch(unsigned int address, unsigned int count, uint8_t* dataPtr, bool* memDonePtr);

private:
	uint8_t* memPtr;
	uint8_t memSize;

};

Memory& getMemory();