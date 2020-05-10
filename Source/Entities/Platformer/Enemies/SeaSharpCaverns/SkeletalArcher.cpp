#include "SkeletalArcher.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SkeletalArcher::MapKey = "skeletal-archer";

SkeletalArcher* SkeletalArcher::deserialize(ValueMap& properties)
{
	SkeletalArcher* instance = new SkeletalArcher(properties);

	instance->autorelease();

	return instance;
}

SkeletalArcher::SkeletalArcher(ValueMap& properties) : super(properties,
	SkeletalArcher::MapKey,
	EntityResources::Enemies_SeaSharpCaverns_SkeletalArcher_Animations,
	EntityResources::Enemies_SeaSharpCaverns_SkeletalArcher_Emblem,
	Size(128.0f, 216.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

SkeletalArcher::~SkeletalArcher()
{
}

Vec2 SkeletalArcher::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* SkeletalArcher::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_SeaSharpCaverns_SkeletalArcher::create();
}
