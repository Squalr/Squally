#include "SkeletalNecromancer.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SkeletalNecromancer::MapKey = "skeletal-necromancer";

SkeletalNecromancer* SkeletalNecromancer::deserialize(ValueMap& properties)
{
	SkeletalNecromancer* instance = new SkeletalNecromancer(properties);

	instance->autorelease();

	return instance;
}

SkeletalNecromancer::SkeletalNecromancer(ValueMap& properties) : super(properties,
	SkeletalNecromancer::MapKey,
	EntityResources::Enemies_SeaSharpCaverns_SkeletalNecromancer_Animations,
	EntityResources::Enemies_SeaSharpCaverns_SkeletalNecromancer_Emblem,
	Size(128.0f, 228.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

SkeletalNecromancer::~SkeletalNecromancer()
{
}

Vec2 SkeletalNecromancer::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* SkeletalNecromancer::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_SeaSharpCaverns_SkeletalNecromancer::create();
}
