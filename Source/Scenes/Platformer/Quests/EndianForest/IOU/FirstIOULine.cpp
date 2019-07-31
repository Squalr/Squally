#include "FirstIOULine.h"

#include "Engine/Quests/QuestTask.h"
#include "Scenes/Platformer/Quests/EndianForest/Intro/MeetFlyBot.h"
#include "Scenes/Platformer/Quests/EndianForest/Intro/HelpSquallyHeal.h"
#include "Scenes/Platformer/Quests/EndianForest/Intro/SpotOrcGrunt.h"
#include "Scenes/Platformer/Quests/EndianForest/Intro/TeachHackerMode.h"

using namespace cocos2d;

const std::string FirstIOULine::MapKeyQuestLineIntro = "first-iou";

FirstIOULine* FirstIOULine::create(std::string quest, std::string questTag, GameObject* owner)
{
	FirstIOULine* instance = new FirstIOULine(quest, questTag, owner);
	
	instance->autorelease();

	return instance;
}

FirstIOULine::FirstIOULine(std::string quest, std::string questTag, GameObject* owner) : super(
	FirstIOULine::MapKeyQuestLineIntro,
	quest,
	questTag,
	{
		(QuestTask*)MeetFlyBot::create(quest == MeetFlyBot::MapKeyQuest ? owner : nullptr),
		(QuestTask*)HelpSquallyHeal::create(quest == HelpSquallyHeal::MapKeyQuest ? owner : nullptr),
		(QuestTask*)TeachHackerMode::create(quest == TeachHackerMode::MapKeyQuest ? owner : nullptr),
		(QuestTask*)SpotOrcGrunt::create(quest == SpotOrcGrunt::MapKeyQuest ? owner : nullptr),
	})
{
}

FirstIOULine::~FirstIOULine()
{
}

void FirstIOULine::initializePositions()
{
	super::initializePositions();
}

void FirstIOULine::initializeListeners()
{
	super::initializeListeners();
}
