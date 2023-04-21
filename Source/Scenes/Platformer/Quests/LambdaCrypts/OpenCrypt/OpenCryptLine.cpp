#include "OpenCryptLine.h"

#include "Engine/Quests/QuestTask.h"
#include "Scenes/Platformer/Quests/LambdaCrypts/OpenCrypt/EnterCrypts.h"
#include "Scenes/Platformer/Quests/LambdaCrypts/OpenCrypt/SecondEncounter.h"
#include "Scenes/Platformer/Quests/LambdaCrypts/OpenCrypt/ThirdEncounter.h"

using namespace cocos2d;

const std::string OpenCryptLine::MapKeyQuestLine = "open-crypt";

OpenCryptLine* OpenCryptLine::create()
{
	OpenCryptLine* instance = new OpenCryptLine();

	instance->autorelease();

	return instance;
}

OpenCryptLine::OpenCryptLine() : super(OpenCryptLine::MapKeyQuestLine,
	{
		QuestData(EnterCrypts::MapKeyQuest, true, [](GameObject* owner, QuestLine* questLine) { return EnterCrypts::create(owner, questLine); }),
		QuestData(SecondEncounter::MapKeyQuest, true, [](GameObject* owner, QuestLine* questLine) { return SecondEncounter::create(owner, questLine); }),
		QuestData(ThirdEncounter::MapKeyQuest, true, [](GameObject* owner, QuestLine* questLine) { return ThirdEncounter::create(owner, questLine); }),
	})
{
}

OpenCryptLine::~OpenCryptLine()
{
}

QuestLine* OpenCryptLine::clone()
{
	return OpenCryptLine::create();
}
