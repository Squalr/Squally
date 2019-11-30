#include "PlatformerBannerDeserializer.h"

#include "cocos/base/CCValue.h"

#include "Engine/Maps/GameObject.h"
#include "Engine/Quests/QuestTask.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/StrUtils.h"
#include "Scenes/Platformer/Quests/PlatformerQuests.h"

#include "Strings/Strings.h"

using namespace cocos2d;

PlatformerBannerDeserializer* PlatformerBannerDeserializer::create()
{
	PlatformerBannerDeserializer* instance = new PlatformerBannerDeserializer();

	instance->autorelease();

	return instance;
}

PlatformerBannerDeserializer::PlatformerBannerDeserializer() : super()
{
	this->deserializers["ef-town-main"] = [=]() { return Strings::Platformer_MapNames_EndianForest_TownMain::create(); };
}

PlatformerBannerDeserializer::~PlatformerBannerDeserializer()
{
}
