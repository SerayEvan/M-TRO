#ifndef EMULATOR
#define EMULATOR

struct MaterialRestriction
{
	uint32_t maxMemoryAloc = 1073741824; // 1 Goi
	uint32_t sizeOfPile = 1048576; // 1 Moi
	uint32_t maxSizeOfProg = 1048576; // 1 Moi
};

struct Emulator
{
	bool run;

	void* pile;
	void* prog;

	void* rPile;
	void* rProg;

	uint32_t sizeOfPile;
	uint32_t sizeOfProg;

	uint32_t meroryAloc;

	//uint32_t pileCursor;
	//uint32_t progCursor;

	MaterialRestriction material;
};

Emulator emulator;

#endif