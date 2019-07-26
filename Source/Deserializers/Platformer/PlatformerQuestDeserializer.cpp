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
	this->deserializers = std::map<std::string, std::function<GameObject*()>>();

	this->deserializers[IntroLine::MapKeyQuestLineIntro] = [=]() { return (GameObject*)IntroLine::create(); };
}

PlatformerQuestDeserializer::~PlatformerQuestDeserializer()
{
}

void PlatformerQuestDeserializer::deserialize(QuestDeserializer::QuestDeserializationRequestArgs args)
{
	if (args.targetObject != nullptr && this->deserializers.find(args.quest) != this->deserializers.end())
	{
		args.targetObject->addChild(this->deserializers[args.quest]());
	}
	else
	{
		CCLOG("Unknown quest encountered: %s", args.quest.c_str());
	}
}
