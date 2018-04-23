#include "PlushieMonkey.h"

int PlushieMonkey::puzzleLock = 0;

PlushieMonkey* PlushieMonkey::create()
{
	PlushieMonkey* instance = new PlushieMonkey();

	instance->autorelease();

	return instance;
}

PlushieMonkey::PlushieMonkey()
{
	this->sprite = Sprite::create(Resources::Plushies_MONKEY);

	this->registerHackables();

	this->chest->contentNode->addChild(this->sprite);

	this->scheduleUpdate();
}

PlushieMonkey::~PlushieMonkey()
{
}

void PlushieMonkey::update(float dt)
{
	void* assemblyAddressStart = nullptr;
	void* assemblyAddressEnd = nullptr;

	__asm
	{
		push eax;
		mov eax, PlushieMonkey::puzzleLock
	}
	
	HACKABLE_CODE_BEGIN(assemblyAddressStart, puzzleStart)
	__asm
	{
		inc eax;
		nop;
		nop;
		nop;
		nop;
	}
	HACKABLE_CODE_END(assemblyAddressEnd, puzzleEnd)

	__asm
	{
		mov PlushieMonkey::puzzleLock, eax
		pop eax;
	}

	this->puzzleData->registerCode(assemblyAddressStart, assemblyAddressEnd, "Puzzle Increment", Resources::Menus_HackerModeMenu_CodeSocket, Resources::Menus_HackerModeMenu_Icons_Safe);
	this->puzzleData->registerCode((void*)((int)assemblyAddressStart + 1), assemblyAddressEnd, "Puzzle Test", Resources::Menus_HackerModeMenu_CodeSocket, Resources::Menus_HackerModeMenu_Icons_Anvil);
	this->puzzleData->registerCode((void*)((int)assemblyAddressStart + 2), assemblyAddressEnd, "Puzzle Swag", Resources::Menus_HackerModeMenu_CodeSocket, Resources::Menus_HackerModeMenu_Icons_BookCrystal);
}

void PlushieMonkey::registerHackables()
{
	Plushie::registerHackables();

	this->puzzleData = HackableData::create("Key", &PlushieMonkey::puzzleLock, &typeid(PlushieMonkey::puzzleLock), Resources::Menus_HackerModeMenu_DataSocket, Resources::Menus_HackerModeMenu_Icons_Lock);
	this->registerData(this->puzzleData);
	
	this->registerData(HackableData::create("Health", this->chest, &typeid((int)this->chest), Resources::Menus_HackerModeMenu_DataSocket, Resources::Menus_HackerModeMenu_Icons_Heart));
	//this->registerCode(HackableCode::create("Test", this->chest, 10, Resources::Menus_HackerModeMenu_CodeSocket, Resources::Menus_HackerModeMenu_Icons_AlchemyPot));
}
