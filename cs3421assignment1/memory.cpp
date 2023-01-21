#include "memory.h"

using namespace std;
void Memory::Parse(FILE* infile)
{
	char* commandC = new char;
	fscanf(infile, "%s", commandC);
	string command(commandC);
	free(commandC);
	if (command == "create") {
		unsigned int* size = new unsigned int;
		fscanf(infile, "%X", size);
		create(*size);
	}
	else if (command == "reset") {
		reset();
	}
	else if (command == "dump") {
		unsigned int* address = new unsigned int;
		fscanf(infile, "%X", address);
		unsigned int* count = new unsigned int;
		fscanf(infile, "%X", count);
		dump(*address, *count);
	}
	else if (command == "set") {
		unsigned int* address = new unsigned int;
		unsigned int* count = new unsigned int;
		fscanf(infile, "%X", address);
		fscanf(infile, "%X", count);
		set(*address, *count, infile);
	}
}

void Memory::create(unsigned int size)
{
	uint8_t* memStart = memPtr + memSize;
	memStart = new uint8_t[size];
	memSize += size;
}

void Memory::reset()
{
	uint8_t* address = memPtr;
	for (uint8_t i = 0; i < memSize; i++) {
		*address = 0;
		address++;
	}
}

void Memory::dump(uint8_t start, uint8_t count)
{
	uint8_t* address = memPtr + start;

	uint8_t startRow = start & 0x10;
	startRow >>= startRow;

	uint8_t startCol = start & 0x01;

	uint8_t endRow = (start + count) & 0x10;
	endRow >>= endRow;

	uint8_t endCol = (start + count) & 0x01;

	fprintf(stdout, "%s", "Addr 00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F\n");
	for (uint8_t i = startCol; i <= endCol; i++) {
		fprintf(stdout, "%s%X%s", "0x", i, "0 ");
		if (i == startRow && i == endRow) {
			for (uint8_t j = 0; j < startCol; j++) 
				fprintf(stdout, "%s", "   ");
			for (uint8_t j = startCol; j <= endCol; j++) {
				fprintf(stdout, "%X", *address);
				address++;
			}
			for (uint8_t j = endCol + 1; j < 15; j++)
				fprintf(stdout, "%s", "   ");
			fprintf(stdout, "%c", '\n');
		}
		else if (i == startRow) {
			for (uint8_t j = 0; j < startCol; j++) {
				fprintf(stdout, "%s", "   ");
			}
			for (uint8_t j = startCol; j <= 15; j++) {
				fprintf(stdout, "%X", *address);
				address++;
			}
			fprintf(stdout, "%c", '\n');
		}
		else if (i == endRow) {
			for (uint8_t j = 0; j < endCol; j++) {
				fprintf(stdout, "%X", *address);
				address++;
			}
			fprintf(stdout, "%c", '\n');
		}
		else {
			for (uint8_t j = 0; j < 16; j++) {
				fprintf(stdout, "%X", *address);
				address++;
			}
		}
	}
}

void Memory::set(uint8_t start, uint8_t count, FILE* infile)
{
	uint8_t* address = memPtr + start;
	for (uint8_t i = 0; i < count; i++) {
		uint8_t* setByte;
		fscanf(infile, "%X", setByte);
		*address = *setByte;
		address++;
	}
}

void Memory::startFetch(unsigned int address, unsigned int count, uint8_t* dataPtr, bool* memDonePtr)
{
	if (count == 1)
		*dataPtr = memPtr[address];
	else
		memcpy(dataPtr, memPtr + address, count);

	*memDonePtr = true;
}

Memory& getMemory()
{
	static Memory mem;
	return mem;
}
