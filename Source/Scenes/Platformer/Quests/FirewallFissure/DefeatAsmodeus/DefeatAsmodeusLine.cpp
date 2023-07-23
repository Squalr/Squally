#include "DefeatAsmodeusLine.h"

#include "Engine/Quests/QuestTask.h"
#include "Scenes/Platformer/Quests/FirewallFissure/DefeatAsmodeus/CraftHeliumBomb.h"
#include "Scenes/Platformer/Quests/FirewallFissure/DefeatAsmodeus/DefeatAsmodeus.h"
#include "Scenes/Platformer/Quests/FirewallFissure/DefeatAsmodeus/DeliverBomb.h"
#include "Scenes/Platformer/Quests/FirewallFissure/DefeatAsmodeus/LavaFlood.h"
#include "Scenes/Platformer/Quests/FirewallFissure/DefeatAsmodeus/TalkToQueenElise.h"
#include "Scenes/Platformer/Quests/FirewallFissure/DefeatAsmodeus/QueenEliseInterim.h"
#include "Scenes/Platformer/Quests/FirewallFissure/DefeatAsmodeus/WantedPosterGone.h"

using namespace cocos2d;

const std::string DefeatAsmodeusLine::MapKeyQuestLine = "defeat-asmodeus";

DefeatAsmodeusLine* DefeatAsmodeusLine::create()
{
	DefeatAsmodeusLine* instance = new DefeatAsmodeusLine();

	instance->autorelease();

	return instance;
}

DefeatAsmodeusLine::DefeatAsmodeusLine() : super(DefeatAsmodeusLine::MapKeyQuestLine, {
	QuestData(TalkToQueenElise::MapKeyQuest, true, [](GameObject* owner, QuestLine* questLine) { return TalkToQueenElise::create(owner, questLine); }),
	QuestData(CraftHeliumBomb::MapKeyQuest, true, [](GameObject* owner, QuestLine* questLine) { return CraftHeliumBomb::create(owner, questLine); }),
	QuestData(DeliverBomb::MapKeyQuest, true, [](GameObject* owner, QuestLine* questLine) { return DeliverBomb::create(owner, questLine); }),
	QuestData(LavaFlood::MapKeyQuest, true, [](GameObject* owner, QuestLine* questLine) { return LavaFlood::create(owner, questLine); }),
	QuestData(QueenEliseInterim::MapKeyQuest, true, [](GameObject* owner, QuestLine* questLine) { return QueenEliseInterim::create(owner, questLine); }),
	QuestData(DefeatAsmodeus::MapKeyQuest, false, [](GameObject* owner, QuestLine* questLine) { return DefeatAsmodeus::create(owner, questLine); }),
	QuestData(WantedPosterGone::MapKeyQuest, true, [](GameObject* owner, QuestLine* questLine) { return WantedPosterGone::create(owner, questLine); }),
})
{
}

DefeatAsmodeusLine::~DefeatAsmodeusLine()
{
}

QuestLine* DefeatAsmodeusLine::clone()
{
	return DefeatAsmodeusLine::create();
}
