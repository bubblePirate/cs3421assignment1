class Clock
{
public:
	void Parse(FILE* infile);
	void reset();
	void tick(int numTicks);
	void dump();

private:
	uint8_t count;
};

Clock& getClock();