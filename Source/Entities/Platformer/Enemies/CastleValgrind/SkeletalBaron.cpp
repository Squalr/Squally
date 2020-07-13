#include "SkeletalBaron.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SkeletalBaron::MapKey = "skeletal-baron";

SkeletalBaron* SkeletalBaron::deserialize(ValueMap& properties)
{
	SkeletalBaron* instance = new SkeletalBaron(properties);

	instance->autorelease();

	return instance;
}

SkeletalBaron::SkeletalBaron(ValueMap& properties) : super(properties,
	SkeletalBaron::MapKey,
	EntityResources::Enemies_CastleValgrind_SkeletalBaron_Animations,
	EntityResources::Enemies_CastleValgrind_SkeletalBaron_Emblem,
	Size(112.0f, 368.0f),
	0.8f,
	Vec2(0.0f, 0.0f))
{
}

SkeletalBaron::~SkeletalBaron()
{
}

Vec2 SkeletalBaron::getDialogueOffset()
{
	return Vec2(16.0f, -112.0f);
}

LocalizedString* SkeletalBaron::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_CastleValgrind_SkeletalBaron::create();
}
