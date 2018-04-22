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
}

PlushieMonkey::~PlushieMonkey()
{
}

void PlushieMonkey::update(float dt)
{
	__asm
	{
		push eax;
		mov eax, PlushieMonkey::puzzleLock
	}
startIncrementPower:
	__asm
	{
		inc eax;
		nop;
		nop;
		nop;
		nop;
	}
endIncrementPower:
	__asm
	{
		mov PlushieMonkey::puzzleLock, eax
		pop eax;
	}

	static bool init = false;

	if (!init)
	{
		init = true;

		void* assemblyAddressStart = nullptr;
		void* assemblyAddressEnd = nullptr;

		__asm
		{
			mov assemblyAddressStart, offset startIncrementPower
			mov assemblyAddressEnd, offset endIncrementPower
		}

		int byteCount = (unsigned int)assemblyAddressEnd - (unsigned int)assemblyAddressStart;
		HackableCode* hackablePower = HackableCode::create("Recharge Power", assemblyAddressStart, byteCount, Resources::Menus_HackerModeMenu_Icons_Heart, Resources::Menus_HackerModeMenu_Icons_Heart);
		this->registerCode(hackablePower);
	}
}

void PlushieMonkey::registerHackables()
{
	Plushie::registerHackables();

	this->registerData(HackableData::create("Key", this->chest, &typeid((int)this->chest), Resources::Minigames_Hexium_Socket, Resources::Menus_HackerModeMenu_Icons_Lock));
	this->registerData(HackableData::create("Key", this->chest, &typeid((int)this->chest), Resources::Minigames_Hexium_Socket, Resources::Menus_HackerModeMenu_Icons_Heart));
	this->registerCode(HackableCode::create("Test", this->chest, 10, Resources::Minigames_Hexium_Socket, Resources::Menus_HackerModeMenu_Icons_AlchemyPot));
}
