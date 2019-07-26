#include "IntroLine.h"

#include "Engine/Quests/Quest.h"
#include "Scenes/Platformer/Quests/EndianForest/Intro/MeetFlyBot.h"

using namespace cocos2d;

const std::string IntroLine::MapKeyQuestLineIntro = "intro";

IntroLine* IntroLine::create()
{
	IntroLine* instance = new IntroLine();
	
	instance->autorelease();

	return instance;
}

IntroLine::IntroLine() : super(
	IntroLine::MapKeyQuestLineIntro,
	{
		(Quest*)MeetFlyBot::create(),
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
