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
	this->lineDeserializers = std::map<std::string, std::function<QuestLine*()>>();

	this->lineDeserializers[DeveloperLine::MapKeyQuestLine] = [=]() { return (QuestLine*)DeveloperLine::create(); };
	this->lineDeserializers[IntroLine::MapKeyQuestLine] = [=]() { return (QuestLine*)IntroLine::create(); };
	this->lineDeserializers[FirstIOULine::MapKeyQuestLine] = [=]() { return (QuestLine*)FirstIOULine::create(); };
	
}

PlatformerQuestDeserializer::~PlatformerQuestDeserializer()
{
}
