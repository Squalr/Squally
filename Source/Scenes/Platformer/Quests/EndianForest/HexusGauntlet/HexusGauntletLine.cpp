#include "HexusGauntletLine.h"

#include "Engine/Quests/QuestTask.h"
#include "Scenes/Platformer/Quests/EndianForest/HexusGauntlet/BeatTutorialA.h"
#include "Scenes/Platformer/Quests/EndianForest/HexusGauntlet/BeatTutorialB.h"
#include "Scenes/Platformer/Quests/EndianForest/HexusGauntlet/BeatTutorialC.h"
#include "Scenes/Platformer/Quests/EndianForest/HexusGauntlet/BeatTutorialD.h"
#include "Scenes/Platformer/Quests/EndianForest/HexusGauntlet/BeatTutorialE.h"
#include "Scenes/Platformer/Quests/EndianForest/HexusGauntlet/BeatTutorialF.h"
#include "Scenes/Platformer/Quests/EndianForest/HexusGauntlet/ReturnToSarude.h"
#include "Scenes/Platformer/Quests/EndianForest/HexusGauntlet/TalkToSarude.h"

using namespace cocos2d;

const std::string HexusGauntletLine::MapKeyQuestLine = "hexus-gauntlet";

HexusGauntletLine* HexusGauntletLine::create()
{
	HexusGauntletLine* instance = new HexusGauntletLine();

	instance->autorelease();

	return instance;
}

HexusGauntletLine::HexusGauntletLine() : super(HexusGauntletLine::MapKeyQuestLine, {
	QuestData(TalkToSarude::MapKeyQuest, true, [=](GameObject* owner, QuestLine* questLine, std::string questTag) { return TalkToSarude::create(owner, questLine, questTag); }),
	QuestData(BeatTutorialA::MapKeyQuest, true, [=](GameObject* owner, QuestLine* questLine, std::string questTag) { return BeatTutorialA::create(owner, questLine, questTag); }),
	QuestData(BeatTutorialB::MapKeyQuest, true, [=](GameObject* owner, QuestLine* questLine, std::string questTag) { return BeatTutorialB::create(owner, questLine, questTag); }),
	QuestData(BeatTutorialC::MapKeyQuest, true, [=](GameObject* owner, QuestLine* questLine, std::string questTag) { return BeatTutorialC::create(owner, questLine, questTag); }),
	QuestData(BeatTutorialD::MapKeyQuest, true, [=](GameObject* owner, QuestLine* questLine, std::string questTag) { return BeatTutorialD::create(owner, questLine, questTag); }),
	QuestData(BeatTutorialE::MapKeyQuest, true, [=](GameObject* owner, QuestLine* questLine, std::string questTag) { return BeatTutorialE::create(owner, questLine, questTag); }),
	QuestData(BeatTutorialF::MapKeyQuest, false, [=](GameObject* owner, QuestLine* questLine, std::string questTag) { return BeatTutorialF::create(owner, questLine, questTag); }),
	QuestData(ReturnToSarude::MapKeyQuest, false, [=](GameObject* owner, QuestLine* questLine, std::string questTag) { return ReturnToSarude::create(owner, questLine, questTag); }),
})
{
}

HexusGauntletLine::~HexusGauntletLine()
{
}
