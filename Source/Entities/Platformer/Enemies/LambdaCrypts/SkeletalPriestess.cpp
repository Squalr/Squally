#include "SkeletalPriestess.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SkeletalPriestess::MapKey = "skeletal-priestess";

SkeletalPriestess* SkeletalPriestess::deserialize(ValueMap& properties)
{
	SkeletalPriestess* instance = new SkeletalPriestess(properties);

	instance->autorelease();

	return instance;
}

SkeletalPriestess::SkeletalPriestess(ValueMap& properties) : super(properties,
	SkeletalPriestess::MapKey,
	EntityResources::Enemies_LambdaCrypts_SkeletalPriestess_Animations,
	EntityResources::Enemies_LambdaCrypts_SkeletalPriestess_Emblem,
	Size(196.0f, 312.0f),
	0.8f,
	Vec2(0.0f, 0.0f))
{
}

SkeletalPriestess::~SkeletalPriestess()
{
}

Vec2 SkeletalPriestess::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* SkeletalPriestess::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_LambdaCrypts_SkeletalPriestess::create();
}
