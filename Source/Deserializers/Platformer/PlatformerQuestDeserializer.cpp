#include "PlatformerQuestDeserializer.h"

#include "cocos/base/CCValue.h"

#include "Engine/Maps/GameObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Scenes/Platformer/Quests/PlatformerQuests.h"

using namespace cocos2d;

const std::string PlatformerQuestDeserializer::MapKeyTypeObject = "object";

PlatformerQuestDeserializer* PlatformerQuestDeserializer::create()
{
	PlatformerQuestDeserializer* instance = new PlatformerQuestDeserializer();

	instance->autorelease();

	return instance;
}

PlatformerQuestDeserializer::PlatformerQuestDeserializer() : super()
{
	this->deserializers = std::map<std::string, std::function<GameObject*(std::string, std::string, GameObject*)>>();

	this->deserializers[IntroLine::MapKeyQuestLineIntro] = [=](std::string quest, std::string questTag, GameObject* owner) { return (GameObject*)IntroLine::create(quest, questTag, owner); };
}

PlatformerQuestDeserializer::~PlatformerQuestDeserializer()
{
}

void PlatformerQuestDeserializer::deserialize(QuestDeserializer::QuestDeserializationRequestArgs args)
{
	if (args.targetObject != nullptr && this->deserializers.find(args.questLine) != this->deserializers.end())
	{
		args.targetObject->addChild(this->deserializers[args.questLine](args.quest, args.questTag, args.targetObject));
	}
	else
	{
		CCLOG("Unknown quest line encountered: %s", args.questLine.c_str());
	}
}
