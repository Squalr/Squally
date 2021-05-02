#include "SkeletalPirate.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SkeletalPirate::MapKey = "skeletal-pirate";

SkeletalPirate* SkeletalPirate::deserialize(ValueMap& properties)
{
	SkeletalPirate* instance = new SkeletalPirate(properties);

	instance->autorelease();

	return instance;
}

SkeletalPirate::SkeletalPirate(ValueMap& properties) : super(properties,
	SkeletalPirate::MapKey,
	EntityResources::Enemies_DataMines_SkeletalPirate_Animations,
	EntityResources::Enemies_DataMines_SkeletalPirate_Emblem,
	Size(112.0f, 820.0f),
	0.8f,
	Vec2(0.0f, 0.0f))
{
}

SkeletalPirate::~SkeletalPirate()
{
}

Vec2 SkeletalPirate::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* SkeletalPirate::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_DataMines_SkeletalPirate::create();
}
