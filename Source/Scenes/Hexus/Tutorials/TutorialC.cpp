#include "TutorialC.h"

TutorialC* TutorialC::create()
{
	TutorialC* instance = new TutorialC();

	instance->autorelease();

	return instance;
}

TutorialC::TutorialC() : StateOverride(
	1,
	1,
	true,
	false,
	true,
	std::vector<CardData*> {},
	std::vector<CardData*> {},
	std::vector<CardData*> {},
	std::vector<CardData*> {},
	std::vector<CardData*> {},
	std::vector<CardData*> {},
	std::vector<CardData*> {},
	std::vector<CardData*> {},
	std::vector<CardData*> {},
	std::vector<CardData*> {})
{
}

TutorialC::~TutorialC()
{
}
