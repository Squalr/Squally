#include "SkeletalWarrior.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SkeletalWarrior::MapKey = "skeletal-warrior";

SkeletalWarrior* SkeletalWarrior::deserialize(ValueMap& properties)
{
	SkeletalWarrior* instance = new SkeletalWarrior(properties);

	instance->autorelease();

	return instance;
}

SkeletalWarrior::SkeletalWarrior(ValueMap& properties) : super(properties,
	SkeletalWarrior::MapKey,
	EntityResources::Enemies_DataMines_SkeletalWarrior_Animations,
	EntityResources::Enemies_DataMines_SkeletalWarrior_Emblem,
	Size(128.0f, 216.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

SkeletalWarrior::~SkeletalWarrior()
{
}

Vec2 SkeletalWarrior::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* SkeletalWarrior::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_DataMines_SkeletalWarrior::create();
}
