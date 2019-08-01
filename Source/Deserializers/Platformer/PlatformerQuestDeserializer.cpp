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
	this->deserializers = std::map<std::string, std::function<GameObject*(GameObject*, std::string, std::string, std::string)>>();

	this->deserializers[DeveloperLine::MapKeyQuestLine] = [=](GameObject* owner, std::string questLine, std::string questTask, std::string questTag) { return (GameObject*)DeveloperLine::deserialize(owner, questLine, questTask, questTag); };
	this->deserializers[IntroLine::MapKeyQuestLine] = [=](GameObject* owner, std::string questLine, std::string questTask, std::string questTag) { return (GameObject*)IntroLine::deserialize(owner, questLine, questTask, questTag); };
	this->deserializers[FirstIOULine::MapKeyQuestLine] = [=](GameObject* owner, std::string questLine, std::string questTask, std::string questTag) { return (GameObject*)FirstIOULine::deserialize(owner, questLine, questTask, questTag); };
	
}

PlatformerQuestDeserializer::~PlatformerQuestDeserializer()
{
}

void PlatformerQuestDeserializer::deserialize(QuestDeserializer::QuestDeserializationRequestArgs args)
{
	if (args.owner != nullptr && this->deserializers.find(args.questLine) != this->deserializers.end())
	{
		args.owner->addChild(this->deserializers[args.questLine](args.owner, args.questLine, args.questTask, args.questTag));
	}
	else
	{
		CCLOG("Unknown quest line encountered: %s", args.questLine.c_str());
	}
}
