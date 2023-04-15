#include "CraftHellGateCrystalLine.h"

#include "Engine/Quests/QuestTask.h"
#include "Scenes/Platformer/Quests/LambdaCrypts/CraftHellGateCrystal/CraftKey.h"
#include "Scenes/Platformer/Quests/LambdaCrypts/CraftHellGateCrystal/DefeatKingZul.h"
#include "Scenes/Platformer/Quests/LambdaCrypts/CraftHellGateCrystal/OpenDemonPortal.h"

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
		QuestData(DefeatKingZul::MapKeyQuest, true, [](GameObject* owner, QuestLine* questLine) { return DefeatKingZul::create(owner, questLine); }),
		QuestData(CraftKey::MapKeyQuest, true, [](GameObject* owner, QuestLine* questLine) { return CraftKey::create(owner, questLine); }),
		QuestData(OpenDemonPortal::MapKeyQuest, false, [](GameObject* owner, QuestLine* questLine) { return OpenDemonPortal::create(owner, questLine); }),
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
