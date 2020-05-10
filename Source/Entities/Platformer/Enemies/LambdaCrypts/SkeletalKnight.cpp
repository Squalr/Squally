#include "SkeletalKnight.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SkeletalKnight::MapKey = "skeletal-knight";

SkeletalKnight* SkeletalKnight::deserialize(ValueMap& properties)
{
	SkeletalKnight* instance = new SkeletalKnight(properties);

	instance->autorelease();

	return instance;
}

SkeletalKnight::SkeletalKnight(ValueMap& properties) : super(properties,
	SkeletalKnight::MapKey,
	EntityResources::Enemies_LambdaCrypts_SkeletalKnight_Animations,
	EntityResources::Enemies_LambdaCrypts_SkeletalKnight_Emblem,
	Size(212.0f, 280.0f),
	0.8f,
	Vec2(0.0f, 0.0f))
{
}

SkeletalKnight::~SkeletalKnight()
{
}

Vec2 SkeletalKnight::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* SkeletalKnight::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_LambdaCrypts_SkeletalKnight::create();
}
