#include "CraftDemonHeartLine.h"

#include "Engine/Quests/QuestTask.h"
#include "Scenes/Platformer/Quests/LambdaCrypts/CraftDemonHeart/CraftDemonHeart.h"
#include "Scenes/Platformer/Quests/LambdaCrypts/CraftDemonHeart/DefeatKingZul.h"
#include "Scenes/Platformer/Quests/LambdaCrypts/CraftDemonHeart/OpenDemonPortal.h"

using namespace cocos2d;

const std::string CraftDemonHeartLine::MapKeyQuestLine = "craft-hell-gate-crystal";

CraftDemonHeartLine* CraftDemonHeartLine::create()
{
	CraftDemonHeartLine* instance = new CraftDemonHeartLine();

	instance->autorelease();

	return instance;
}

CraftDemonHeartLine::CraftDemonHeartLine() : super(CraftDemonHeartLine::MapKeyQuestLine,
	{
		QuestData(DefeatKingZul::MapKeyQuest, true, [](GameObject* owner, QuestLine* questLine) { return DefeatKingZul::create(owner, questLine); }),
		QuestData(CraftDemonHeart::MapKeyQuest, true, [](GameObject* owner, QuestLine* questLine) { return CraftDemonHeart::create(owner, questLine); }),
		QuestData(OpenDemonPortal::MapKeyQuest, false, [](GameObject* owner, QuestLine* questLine) { return OpenDemonPortal::create(owner, questLine); }),
	})
{
}

CraftDemonHeartLine::~CraftDemonHeartLine()
{
}

QuestLine* CraftDemonHeartLine::clone()
{
	return CraftDemonHeartLine::create();
}
