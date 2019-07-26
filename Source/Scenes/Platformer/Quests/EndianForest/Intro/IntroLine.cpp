#include "IntroLine.h"

#include "Engine/Quests/QuestTask.h"
#include "Scenes/Platformer/Quests/EndianForest/Intro/MeetFlyBot.h"
#include "Scenes/Platformer/Quests/EndianForest/Intro/HelpSquallyHeal.h"
#include "Scenes/Platformer/Quests/EndianForest/Intro/SpotOrcGrunt.h"
#include "Scenes/Platformer/Quests/EndianForest/Intro/TeachHackerMode.h"

using namespace cocos2d;

const std::string IntroLine::MapKeyQuestLineIntro = "intro";

IntroLine* IntroLine::create(GameObject* owner)
{
	IntroLine* instance = new IntroLine(owner);
	
	instance->autorelease();

	return instance;
}

IntroLine::IntroLine(GameObject* owner) : super(
	IntroLine::MapKeyQuestLineIntro,
	{
		(QuestTask*)MeetFlyBot::create(owner),
		(QuestTask*)HelpSquallyHeal::create(owner),
		(QuestTask*)TeachHackerMode::create(owner),
		(QuestTask*)SpotOrcGrunt::create(owner),
	})
{
}

IntroLine::~IntroLine()
{
}

void IntroLine::initializePositions()
{
	super::initializePositions();
}

void IntroLine::initializeListeners()
{
	super::initializeListeners();
}
