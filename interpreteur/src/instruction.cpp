#include "instruction.hpp"

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

		} else if ( *i == "UI8" ) {
			sizeInstruct += SIZEOF_UI8;
		} else if ( *i == "UI16" ) {
			sizeInstruct += SIZEOF_UI16;
		} else if ( *i == "UI32" ) {
			sizeInstruct += SIZEOF_UI32;
		} else if ( *i == "UI64" ) {
			sizeInstruct += SIZEOF_UI64;

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

void InitInstructionTable()
{
	numberInstruction = 0;

	instructionTableData = (InstructionData*)malloc( sizeof(InstructionData) * SIZE_INSTRUCTION_TABLE );
	instructionTable = (InstructionFunc*)malloc( sizeof(InstructionFunc) * SIZE_INSTRUCTION_TABLE );

	/* =======================================
					ROUTINE COMMAND
	======================================= */

	AddInstruction( "NONE", "", [](){
	});

	AddInstruction( "QUIT", "", [](){
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

	AddInstruction( "PRINT", "", [](){

		count << "(void *)( *str )\n";
	});

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
		emulator.rProg = emulator.prog + *(emulator.rPile - *( uint32_t* )emulator.rProg);
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

	auto funcJumpIfEqual = []<typename T>(){

		T* var1 = emulator.rPile - *( uint32_t* )emulator.rProg;
		emulator.rProg += SIZEOF_PI;

		T* var2 = emulator.rPile - *( uint32_t* )emulator.rProg;
		emulator.rProg += SIZEOF_PI;

		uint32_t* posJump = ( uint32_t* )emulator.rProg;
		emulator.rProg += SIZEOF_PR;

		if ( *var1 == *var2 ) {
			emulator.rProg = emulator.prog + *posJump;
		}
	};

	auto funcJumpIfUnEqual = []<typename T>(){

		T* var1 = emulator.rPile - *( uint32_t* )emulator.rProg;
		emulator.rProg += SIZEOF_PI;

		T* var2 = emulator.rPile - *( uint32_t* )emulator.rProg;
		emulator.rProg += SIZEOF_PI;

		uint32_t* posJump = ( uint32_t* )emulator.rProg;
		emulator.rProg += SIZEOF_PR;

		if ( *var1 != *var2 ) {
			emulator.rProg = emulator.prog + *posJump;
		}
	};

	AddInstruction( "JUMP_IF_EQUAL_8" , "PI PI PR", lambda.template funcJumpIfEqual<int8_t> );
	AddInstruction( "JUMP_IF_EQUAL_16", "PI PI PR", lambda.template funcJumpIfEqual<int16_t>);
	AddInstruction( "JUMP_IF_EQUAL_32", "PI PI PR", lambda.template funcJumpIfEqual<int32_t>);
	AddInstruction( "JUMP_IF_EQUAL_64", "PI PI PR", lambda.template funcJumpIfEqual<int64_t>);

	AddInstruction( "JUMP_IF_UNEQUAL_8" , "PI PI PR", lambda.template funcJumpIfUnEqual<int8_t> );
	AddInstruction( "JUMP_IF_UNEQUAL_16", "PI PI PR", lambda.template funcJumpIfUnEqual<int16_t>);
	AddInstruction( "JUMP_IF_UNEQUAL_32", "PI PI PR", lambda.template funcJumpIfUnEqual<int32_t>);
	AddInstruction( "JUMP_IF_UNEQUAL_64", "PI PI PR", lambda.template funcJumpIfUnEqual<int64_t>);

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

	AddInstruction("PUSH_PILE","UI16", [](){

		uint16_t* pilePush = ( uint16_t* )emulator.rProg;
		emulator.rProg += SIZEOF_UI16;

		emulator.rPile += *pilePush;

		*(uint32_t*)(emulator.rPile-1) = *pilePush;

	});

	AddInstruction("PUSH_PILE_VAR","PI", [](){

		uint16_t* pilePush = emulator.rPile - *( uint32_t* )emulator.rProg;
		emulator.rProg += SIZEOF_PI;

		emulator.rPile += SIZEOF_INTERFUNC + *pilePush;

		*(uint32_t*)(emulator.rPile-1) = *pilePush;

	});

	AddInstruction( "JUMP_FORWARD", "PR", [](){

		*(uint32_t*)(emulator.rPile-3) = emulator.rProg - emulator.prog + SIZEOF_PR;

		emulator.rProg = emulator.prog + *(uint32_t*)emulator.rProg;
	});

	AddInstruction( "JUMP_FORWARD_VAR", "PI", [](){

		*(uint32_t*)(emulator.rPile-3) = emulator.rProg - emulator.prog + SIZEOF_PI;

		emulator.rProg = emulator.prog + *(emulator.rPile - *( uint32_t* )emulator.rProg);
	});

	AddInstruction("JUMP_BACKWARD","UI32", [](){

		emulator.rProg = emulator.prog + *(uint32_t*)(emulator.rPile-3);
	});

	AddInstruction("PULL_PILE","UI32", [](){

		emulator.rPile -= *(uint32_t*)(emulator.rPile-1);
	});
}