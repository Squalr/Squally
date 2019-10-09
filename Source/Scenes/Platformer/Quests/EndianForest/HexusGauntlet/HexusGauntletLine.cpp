#include "HexusGauntletLine.h"

#include "Engine/Quests/QuestTask.h"
#include "Scenes/Platformer/Quests/EndianForest/HexusGauntlet/BeatTutorialA.h"
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
	QuestData(TalkToSarude::MapKeyQuest, false, [](GameObject* owner, QuestLine* questLine, std::string questTag) { return TalkToSarude::create(owner, questLine, questTag); }),
	QuestData(BeatTutorialA::MapKeyQuest, false, [](GameObject* owner, QuestLine* questLine, std::string questTag) { return BeatTutorialA::create(owner, questLine, questTag); }),
})
{
}

HexusGauntletLine::~HexusGauntletLine()
{
}
