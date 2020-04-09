#include "TrainingDummy.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string TrainingDummy::MapKey = "training-dummy";

TrainingDummy* TrainingDummy::deserialize(ValueMap& properties)
{
	TrainingDummy* instance = new TrainingDummy(properties);

	instance->autorelease();

	return instance;
}

TrainingDummy::TrainingDummy(ValueMap& properties) : super(properties,
	TrainingDummy::MapKey,
	EntityResources::Misc_EndianForest_TrainingDummy_Animations,
	EntityResources::Misc_EndianForest_TrainingDummy_Emblem,
	Size(256.0f, 218.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

TrainingDummy::~TrainingDummy()
{
}

Vec2 TrainingDummy::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* TrainingDummy::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_Misc_TrainingDummy::create();
}
