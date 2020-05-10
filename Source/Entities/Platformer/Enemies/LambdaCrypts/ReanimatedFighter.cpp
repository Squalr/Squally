#include "ReanimatedFighter.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string ReanimatedFighter::MapKey = "reanimated-fighter";

ReanimatedFighter* ReanimatedFighter::deserialize(ValueMap& properties)
{
	ReanimatedFighter* instance = new ReanimatedFighter(properties);

	instance->autorelease();

	return instance;
}

ReanimatedFighter::ReanimatedFighter(ValueMap& properties) : super(properties,
	ReanimatedFighter::MapKey,
	EntityResources::Enemies_LambdaCrypts_ReanimatedFighter_Animations,
	EntityResources::Enemies_LambdaCrypts_ReanimatedFighter_Emblem,
	Size(256.0f, 248.0f),
	0.9f,
	Vec2(0.0f, 0.0f))
{
}

ReanimatedFighter::~ReanimatedFighter()
{
}

Vec2 ReanimatedFighter::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* ReanimatedFighter::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_LambdaCrypts_ReanimatedFighter::create();
}
