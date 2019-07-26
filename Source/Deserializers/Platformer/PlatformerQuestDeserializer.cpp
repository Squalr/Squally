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
	this->deserializers = std::map<std::string, std::function<GameObject*(GameObject*)>>();

	this->deserializers[IntroLine::MapKeyQuestLineIntro] = [=](GameObject* owner) { return (GameObject*)IntroLine::create(owner); };
}

PlatformerQuestDeserializer::~PlatformerQuestDeserializer()
{
}

void PlatformerQuestDeserializer::deserialize(QuestDeserializer::QuestDeserializationRequestArgs args)
{
	if (args.targetObject != nullptr && this->deserializers.find(args.questLine) != this->deserializers.end())
	{
		args.targetObject->addChild(this->deserializers[args.questLine](args.targetObject));
	}
	else
	{
		CCLOG("Unknown quest line encountered: %s", args.questLine.c_str());
	}
}
