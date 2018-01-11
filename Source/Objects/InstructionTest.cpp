#include "InstructionTest.h"

int testVariable = 0;

InstructionTest* InstructionTest::create()
{
	InstructionTest* instructionTest = new InstructionTest();

	instructionTest->autorelease();

	return instructionTest;
}

InstructionTest::InstructionTest()
{
	this->sprite = Sprite::create(Resources::HUD_Egg);
	this->instructionLabel = OutlineLabel::create("Computing assembly...", Resources::Fonts_Montserrat_Medium, 24);

	this->addChild(this->sprite);
	this->addChild(this->instructionLabel);

	this->scheduleUpdate();
}

InstructionTest::~InstructionTest()
{
}

void InstructionTest::update(float dt)
{
	this->elapsed += dt;

	if (this->elapsed > 1.0f)
	{
		this->hackableFunction();
		this->elapsed = 0.0f;
	}
}

void InstructionTest::hackableFunction()
{
	void *assemblyAddressStart = nullptr;
	void *assemblyAddressEnd = nullptr;

	__asm
	{
		mov assemblyAddressStart, offset assemblyStart
		mov assemblyAddressEnd, offset assemblyEnd
	}

assemblyStart:
	__asm
	{
		push eax;
		xor eax, edi;
		inc testVariable;
		xor eax, ebx;
		pop eax;
	}
assemblyEnd:

	byte * bytes = (byte*)assemblyAddressStart;
	int byteCount = (unsigned int)assemblyAddressEnd - (unsigned int)assemblyAddressStart;

	ud_t ud_obj;

	ud_init(&ud_obj);
	ud_set_input_buffer(&ud_obj, bytes, byteCount);
	ud_set_mode(&ud_obj, 32);
	ud_set_syntax(&ud_obj, UD_SYN_INTEL);

	std::string instructions = "";

	while (ud_disassemble(&ud_obj))
	{
		instructions += ud_insn_asm(&ud_obj);
		instructions += "\n";
	}

	auto result = Fasm::assemble(instructions, assemblyAddressStart);


	ud_init(&ud_obj);
	ud_set_input_buffer(&ud_obj, result->OutputData, result->OutputLength);
	ud_set_mode(&ud_obj, 32);
	ud_set_syntax(&ud_obj, UD_SYN_INTEL);

	instructions = "";

	while (ud_disassemble(&ud_obj))
	{
		instructions += ud_insn_asm(&ud_obj);
		instructions += "\n";
	}

	this->instructionLabel->setText(instructions);
}
