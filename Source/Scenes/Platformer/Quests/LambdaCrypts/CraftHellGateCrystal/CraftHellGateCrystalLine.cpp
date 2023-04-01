#include "CraftHellGateCrystalLine.h"

#include "Engine/Quests/QuestTask.h"
#include "Scenes/Platformer/Quests/LambdaCrypts/CraftHellGateCrystal/CraftCrystal.h"

using namespace cocos2d;

const std::string CraftHellGateCrystalLine::MapKeyQuestLine = "craft-hell-gate-crystal";

CraftHellGateCrystalLine* CraftHellGateCrystalLine::create()
{
	CraftHellGateCrystalLine* instance = new CraftHellGateCrystalLine();

	instance->autorelease();

	return instance;
}

CraftHellGateCrystalLine::CraftHellGateCrystalLine() : super(CraftHellGateCrystalLine::MapKeyQuestLine,
	{
		QuestData(CraftCrystal::MapKeyQuest, true, [](GameObject* owner, QuestLine* questLine) { return CraftCrystal::create(owner, questLine); }),
	})
{
}

CraftHellGateCrystalLine::~CraftHellGateCrystalLine()
{
}

QuestLine* CraftHellGateCrystalLine::clone()
{
	return CraftHellGateCrystalLine::create();
}
