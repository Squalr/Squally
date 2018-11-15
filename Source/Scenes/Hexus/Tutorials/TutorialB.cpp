#include "TutorialB.h"

TutorialB* TutorialB::create()
{
	TutorialB* instance = new TutorialB();

	instance->autorelease();

	return instance;
}

TutorialB::TutorialB() : StateOverride(
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

TutorialB::~TutorialB()
{
}
