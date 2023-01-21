#include "RezLazarusLine.h"

#include "Engine/Quests/QuestTask.h"
#include "Scenes/Platformer/Quests/LambdaCrypts/RezLazarus/RezLazarus.h"

using namespace cocos2d;

const std::string RezLazarusLine::MapKeyQuestLine = "rez-lazarus";

RezLazarusLine* RezLazarusLine::create()
{
	RezLazarusLine* instance = new RezLazarusLine();

	instance->autorelease();

	return instance;
}

RezLazarusLine::RezLazarusLine() : super(RezLazarusLine::MapKeyQuestLine,
	{
		QuestData(RezLazarus::MapKeyQuest, true, [](GameObject* owner, QuestLine* questLine) { return RezLazarus::create(owner, questLine); }),
	})
{
}

RezLazarusLine::~RezLazarusLine()
{
}

QuestLine* RezLazarusLine::clone()
{
	return RezLazarusLine::create();
}
