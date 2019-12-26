#include "HexusGauntletLine.h"

#include "Engine/Quests/QuestTask.h"
#include "Scenes/Platformer/Quests/EndianForest/HexusGauntlet/BeatTutorialA.h"
#include "Scenes/Platformer/Quests/EndianForest/HexusGauntlet/BeatTutorialB.h"
#include "Scenes/Platformer/Quests/EndianForest/HexusGauntlet/BeatTutorialC.h"
#include "Scenes/Platformer/Quests/EndianForest/HexusGauntlet/BeatTutorialD.h"
#include "Scenes/Platformer/Quests/EndianForest/HexusGauntlet/BeatTutorialE.h"
#include "Scenes/Platformer/Quests/EndianForest/HexusGauntlet/BeatTutorialF.h"
#include "Scenes/Platformer/Quests/EndianForest/HexusGauntlet/ReturnToMarcel.h"
#include "Scenes/Platformer/Quests/EndianForest/HexusGauntlet/TalkToMarcel.h"

using namespace cocos2d;

const std::string HexusGauntletLine::MapKeyQuestLine = "hexus-gauntlet";

HexusGauntletLine* HexusGauntletLine::create()
{
	HexusGauntletLine* instance = new HexusGauntletLine();

	instance->autorelease();

	return instance;
}

HexusGauntletLine::HexusGauntletLine() : super(HexusGauntletLine::MapKeyQuestLine, {
	QuestData(TalkToMarcel::MapKeyQuest, false, [=](GameObject* owner, QuestLine* questLine) { return TalkToMarcel::create(owner, questLine); }),
	QuestData(BeatTutorialA::MapKeyQuest, true, [=](GameObject* owner, QuestLine* questLine) { return BeatTutorialA::create(owner, questLine); }),
	QuestData(BeatTutorialB::MapKeyQuest, true, [=](GameObject* owner, QuestLine* questLine) { return BeatTutorialB::create(owner, questLine); }),
	QuestData(BeatTutorialC::MapKeyQuest, true, [=](GameObject* owner, QuestLine* questLine) { return BeatTutorialC::create(owner, questLine); }),
	QuestData(BeatTutorialD::MapKeyQuest, true, [=](GameObject* owner, QuestLine* questLine) { return BeatTutorialD::create(owner, questLine); }),
	QuestData(BeatTutorialE::MapKeyQuest, true, [=](GameObject* owner, QuestLine* questLine) { return BeatTutorialE::create(owner, questLine); }),
	QuestData(BeatTutorialF::MapKeyQuest, true, [=](GameObject* owner, QuestLine* questLine) { return BeatTutorialF::create(owner, questLine); }),
	QuestData(ReturnToMarcel::MapKeyQuest, false, [=](GameObject* owner, QuestLine* questLine) { return ReturnToMarcel::create(owner, questLine); }),
})
{
}

HexusGauntletLine::~HexusGauntletLine()
{
}

QuestLine* HexusGauntletLine::clone()
{
	return HexusGauntletLine::create();
}
