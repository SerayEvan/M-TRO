
#include "instruction.hpp"

InstructionData* instructionTableData;
InstructionFunc* instructionTable;
uint16_t numberInstruction = 0;

void AddInstruction( string name, string inputSyntaxe, const InstructionFunc func )
{
	instructionTableData[numberInstruction].id = numberInstruction;
	instructionTableData[numberInstruction].name = name;
	instructionTableData[numberInstruction].inputSyntaxe = inputSyntaxe;

	uint32_t sizeInstruct = 2;

	auto input = split(inputSyntaxe);
	for (auto i = input.begin(); i < input.end(); ++i)
	{
		if ( *i == "I8" ) {
			sizeInstruct += SIZEOF_I8;
		} else if ( *i == "I16" ) {
			sizeInstruct += SIZEOF_I16;
		} else if ( *i == "I32" ) {
			sizeInstruct += SIZEOF_I32;
		} else if ( *i == "I64" ) {
			sizeInstruct += SIZEOF_I64;

		} else if ( *i == "U8" ) {
			sizeInstruct += SIZEOF_U8;
		} else if ( *i == "U16" ) {
			sizeInstruct += SIZEOF_U16;
		} else if ( *i == "U32" ) {
			sizeInstruct += SIZEOF_U32;
		} else if ( *i == "U64" ) {
			sizeInstruct += SIZEOF_U64;

		} else if ( *i == "F" ) {
			sizeInstruct += SIZEOF_F;

		} else if ( *i == "D" ) {
			sizeInstruct += SIZEOF_D;

		} else if ( *i == "C" ) {
			sizeInstruct += SIZEOF_C;

		} else if ( *i == "PI" ) {
			sizeInstruct += SIZEOF_PI;

		} else if ( *i == "PR" ) {
			sizeInstruct += SIZEOF_PR;
		}
	}

	instructionTableData[numberInstruction].sizeofInstruction = sizeInstruct;

	instructionTable[numberInstruction] = func;

	numberInstruction++;
}

template<typename T>
void initInstructionTableJumpEqual(string typeName)
{
	AddInstruction(
		"JUMP_IF_EQUAL_"+typeName,
		"PI PI PR",
		[](){

			T* var1 = (T*) ( emulator.rPile - *( uint32_t* )emulator.rProg );
			emulator.rProg += SIZEOF_PI;
			T* var2 = (T*) ( emulator.rPile - *( uint32_t* )emulator.rProg );
			emulator.rProg += SIZEOF_PI;

			uint32_t* posJump = ( uint32_t* )emulator.rProg;
			emulator.rProg += SIZEOF_PR;

			if ( *var1 == *var2 ) {
				emulator.rProg = emulator.prog + *posJump;
			}
	});

	AddInstruction(
		"JUMP_IF_UNEQUAL_"+typeName,
		"PI PI PR",
		[](){

			T* var1 = (T*) ( emulator.rPile - *( uint32_t* )emulator.rProg );
			emulator.rProg += SIZEOF_PI;
			T* var2 = (T*) ( emulator.rPile - *( uint32_t* )emulator.rProg );
			emulator.rProg += SIZEOF_PI;

			uint32_t* posJump = ( uint32_t* )emulator.rProg;
			emulator.rProg += SIZEOF_PR;

			if ( *var1 != *var2 ) {
				emulator.rProg = emulator.prog + *posJump;
			}
	});
}

void initInstructionTableJump()
{
	/* =======================================
					JUMP COMMAND
	==========================================
	
	JUMP 		PR destination
	JUMP_VAR	PI destination
		saute a la position donner

	======================================= */

	AddInstruction( "JUMP", "PR", [](){
		emulator.rProg = emulator.prog + *( uint32_t* )emulator.rProg;
	});

	AddInstruction( "JUMP_VAR", "PI", [](){
		emulator.rProg = emulator.prog + *( uint32_t* )(emulator.rPile - *( uint32_t* )emulator.rProg);
	});


	/* =======================================

	JUMP_IF			PI bool, PR destination:
		saute si la variable d'entré est a true

	JUMP_IF_EQUAL	PI v1, PI v2, PR destination:
		saute si les deux entré sont égal

	JUMP_IF_UNEQUAL PI v1, PI v2, PR destination:
		saute si les deux entré sont inégal

	======================================= */

	AddInstruction(
		"JUMP_IF",
		"PI PR",
		[](){

			uint8_t* var1 = (uint8_t*) ( emulator.rPile - *( uint32_t* )emulator.rProg );
			emulator.rProg += SIZEOF_PI;

			uint32_t* posJump = ( uint32_t* )emulator.rProg;
			emulator.rProg += SIZEOF_PR;

			if ( *var1 == 1 ) {
				emulator.rProg = emulator.prog + *posJump;
			}
	});

	initInstructionTableJumpEqual<int8_t>("8");
	initInstructionTableJumpEqual<int8_t>("16");
	initInstructionTableJumpEqual<int8_t>("32");
	initInstructionTableJumpEqual<int8_t>("64");

	/* =======================================
	
	PUSH_PILE		UI16 pileTranslate :
	PUSH_PILE_VAR	PI pileTranslate :
		install un point pour que le back puisse efectuer un retoure
	
	JUMP_FORWARD : même chose que le jump sauf qui garde la position de départ
	BACK_JUMP :
		retourne avent un jump_forward (équivaux return d'une fonction)

	PULL_PILE :
		restore la pile t'elle qu'avent le pushPile

	======================================= */

	AddInstruction("PUSH_PILE","U16", [](){

		uint16_t* pilePush = ( uint16_t* )emulator.rProg;
		emulator.rProg += SIZEOF_UI16;

		emulator.rPile += *pilePush;

		//*(uint32_t*)(emulator.rPile-1) = *pilePush;

	});

	/*AddInstruction("PUSH_PILE_VAR","PI", [](){

		uint16_t* pilePush = ( uint16_t* )( emulator.rPile - *( uint32_t* )emulator.rProg );
		emulator.rProg += SIZEOF_PI;

		emulator.rPile += SIZEOF_INTERFUNC + *pilePush;

		//*(uint32_t*)(emulator.rPile-1) = *pilePush;

	});*/

	AddInstruction( "JUMP_FORWARD", "PR", [](){

		*(uint32_t*)(emulator.rPile) = (emulator.rProg - emulator.prog) + SIZEOF_PR;

		emulator.rProg = emulator.prog + *( uint32_t* )emulator.rProg;
	});

	AddInstruction( "JUMP_FORWARD_VAR", "PI", [](){// pi doit ètre placé aure d'ateinte des argument

		*(uint32_t*)(emulator.rPile) = (emulator.rProg - emulator.prog) + SIZEOF_PI;

		emulator.rProg = emulator.prog + *( uint32_t* )(emulator.rPile + *( uint32_t* )emulator.rProg);
	});

	AddInstruction("JUMP_BACKWARD","U32", [](){

		emulator.rProg = emulator.prog + *( uint32_t* )(emulator.rPile);
	});

	AddInstruction("PULL_PILE","U16", [](){

		uint16_t* pilePush = ( uint16_t* )emulator.rProg;
		emulator.rProg += SIZEOF_UI16;

		emulator.rPile -= *pilePush;
	});
}

void initInstructionTable()
{
	numberInstruction = 0;

	instructionTableData = (InstructionData*)malloc( sizeof(InstructionData) * SIZE_INSTRUCTION_TABLE );
	instructionTable = (InstructionFunc*)malloc( sizeof(InstructionFunc) * SIZE_INSTRUCTION_TABLE );

	/* =======================================
					ROUTINE COMMAND
	======================================= */

	AddInstruction( "NONE", "N", [](){
	});

	AddInstruction( "QUIT", "N", [](){

		emulator.run = false;
	});

	/* =======================================
					PRINT COMMAND
	======================================= */

	/*AddInstruction( "PRINT", "PI", [](){
		
		char** str = emulator.rPile - ( uint32_t* )emulator.rProg;
		emulator.rProg += SIZEOF_PI;

		cout << (void *)( *str );
	});*/

	AddInstruction( "PRINT", "N", [](){

		cout  << "hello word\n";
	});

	initInstructionTableJump();	
}