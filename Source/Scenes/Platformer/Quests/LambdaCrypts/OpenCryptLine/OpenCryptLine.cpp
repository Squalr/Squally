#include "OpenCryptLine.h"

#include "Engine/Quests/QuestTask.h"
#include "Scenes/Platformer/Quests/LambdaCrypts/OpenCryptLine/EnterCrypts.h"

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
