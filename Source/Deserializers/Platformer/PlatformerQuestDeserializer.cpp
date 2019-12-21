#include "PlatformerQuestDeserializer.h"

#include "cocos/base/CCValue.h"

#include "Engine/Maps/GameObject.h"
#include "Engine/Quests/QuestTask.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/StrUtils.h"
#include "Scenes/Platformer/Quests/PlatformerQuests.h"

using namespace cocos2d;

PlatformerQuestDeserializer* PlatformerQuestDeserializer::create()
{
	PlatformerQuestDeserializer* instance = new PlatformerQuestDeserializer();

	instance->autorelease();

	return instance;
}

PlatformerQuestDeserializer::PlatformerQuestDeserializer() : super()
{
	this->lineDeserializers = std::map<std::string, std::function<QuestLine*()>>();

	this->lineDeserializers[BusinessHoursLine::MapKeyQuestLine] = [=]() { return (QuestLine*)BusinessHoursLine::create(); };
	this->lineDeserializers[HexusGauntletLine::MapKeyQuestLine] = [=]() { return (QuestLine*)HexusGauntletLine::create(); };
	this->lineDeserializers[IntroLine::MapKeyQuestLine] = [=]() { return (QuestLine*)IntroLine::create(); };
	this->lineDeserializers[FindElrielLine::MapKeyQuestLine] = [=]() { return (QuestLine*)FindElrielLine::create(); };
	this->lineDeserializers[FerryRepairsLine::MapKeyQuestLine] = [=]() { return (QuestLine*)FerryRepairsLine::create(); };
	this->lineDeserializers[RescueGuanoLine::MapKeyQuestLine] = [=]() { return (QuestLine*)RescueGuanoLine::create(); };
	this->lineDeserializers[SailForRuinsLine::MapKeyQuestLine] = [=]() { return (QuestLine*)SailForRuinsLine::create(); };
}

PlatformerQuestDeserializer::~PlatformerQuestDeserializer()
{
}

void PlatformerQuestDeserializer::deserializeProperties(GameObject* owner, ValueMap properties)
{
	std::string questLine = GameUtils::getKeyOrDefault(properties, GameObject::MapKeyQuestLine, Value("")).asString();
	std::vector<std::string> questTasks = StrUtils::splitOn(
		GameUtils::getKeyOrDefault(properties, GameObject::MapKeyQuest, Value("")).asString(),
		",",
		false
	);
	std::string questTag = GameUtils::getKeyOrDefault(properties, GameObject::MapKeyQuestTag, Value("")).asString();

	if (!questLine.empty())
	{
		for (auto it = questTasks.begin(); it != questTasks.end(); it++)
		{
			QuestTask* quest = this->deserialize(QuestDeserializer::QuestDeserializationRequestArgs(owner, questLine, *it, questTag));

			if (quest != nullptr)
			{
				owner->addChild(quest);
			}
		}
	}
}

std::string PlatformerQuestDeserializer::getPropertyDeserializerKey()
{
	return GameObject::MapKeyQuestLine;
}
