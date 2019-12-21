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
	this->deserializers["elbridge"] = [=]() { return Strings::Platformer_MapNames_EndianForest_Elbridge::create(); };
	this->deserializers["mages-guild"] = [=]() { return Strings::Platformer_MapNames_EndianForest_MagesGuild::create(); };
	this->deserializers["mages-prison"] = [=]() { return Strings::Platformer_MapNames_EndianForest_MagesPrison::create(); };
	this->deserializers["sullen-forest"] = [=]() { return Strings::Platformer_MapNames_EndianForest_SullenForest::create(); };
	this->deserializers["limestone-temple"] = [=]() { return Strings::Platformer_MapNames_EndianForest_LimestoneTemple::create(); };
	this->deserializers["valley-ash"] = [=]() { return Strings::Platformer_MapNames_EndianForest_ValleyOfAsh::create(); };
}

PlatformerBannerDeserializer::~PlatformerBannerDeserializer()
{
}
