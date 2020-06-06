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
	// Misc
	this->deserializers["perilous-sea"] = [=]() { return Strings::Platformer_MapNames_PerilousSea_PerilousSea::create(); };

	// EF
	this->deserializers["endian-forest"] = [=]() { return Strings::Platformer_MapNames_EndianForest_EndianForest::create(); };
	this->deserializers["elbridge"] = [=]() { return Strings::Platformer_MapNames_EndianForest_Elbridge::create(); };
	this->deserializers["mages-guild"] = [=]() { return Strings::Platformer_MapNames_EndianForest_MagesGuild::create(); };
	this->deserializers["mages-prison"] = [=]() { return Strings::Platformer_MapNames_EndianForest_MagesPrison::create(); };
	this->deserializers["sullen-forest"] = [=]() { return Strings::Platformer_MapNames_EndianForest_SullenForest::create(); };
	this->deserializers["limestone-temple"] = [=]() { return Strings::Platformer_MapNames_EndianForest_LimestoneTemple::create(); };
	this->deserializers["fields-of-strife"] = [=]() { return Strings::Platformer_MapNames_EndianForest_FieldsOfStrife::create(); };

	// UR
	this->deserializers["underflow-ruins"] = [=]() { return Strings::Platformer_MapNames_UnderflowRuins_UnderflowRuins::create(); };
	this->deserializers["pyramid-pass"] = [=]() { return Strings::Platformer_MapNames_UnderflowRuins_PyramidPass::create(); };
	this->deserializers["athens"] = [=]() { return Strings::Platformer_MapNames_UnderflowRuins_Athens::create(); };
	this->deserializers["lions-cistern"] = [=]() { return Strings::Platformer_MapNames_UnderflowRuins_LionsCistern::create(); };
	this->deserializers["skys-reach"] = [=]() { return Strings::Platformer_MapNames_UnderflowRuins_SkysReach::create(); };

	// DM
	this->deserializers["data-mines"] = [=]() { return Strings::Platformer_MapNames_DataMines_DataMines::create(); };

	// CV
	this->deserializers["castle-valgrind"] = [=]() { return Strings::Platformer_MapNames_CastleValgrind_CastleValgrind::create(); };

	// BP
	this->deserializers["ballmer-peaks"] = [=]() { return Strings::Platformer_MapNames_BallmerPeaks_BallmerPeaks::create(); };

	// DH
	this->deserializers["daemons-hallow"] = [=]() { return Strings::Platformer_MapNames_DaemonsHallow_DaemonsHallow::create(); };

	// LC
	this->deserializers["lambda-crypts"] = [=]() { return Strings::Platformer_MapNames_LambdaCrypts_LambdaCrypts::create(); };
	this->deserializers["valley-ash"] = [=]() { return Strings::Platformer_MapNames_LambdaCrypts_ValleyOfAsh::create(); };

	// VS
	this->deserializers["void-star"] = [=]() { return Strings::Platformer_MapNames_VoidStar_VoidStar::create(); };
}

PlatformerBannerDeserializer::~PlatformerBannerDeserializer()
{
}
