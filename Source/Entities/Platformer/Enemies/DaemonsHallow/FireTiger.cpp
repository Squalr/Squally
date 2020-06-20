#include "FireTiger.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string FireTiger::MapKey = "fire-tiger";

FireTiger* FireTiger::deserialize(ValueMap& properties)
{
	FireTiger* instance = new FireTiger(properties);

	instance->autorelease();

	return instance;
}

FireTiger::FireTiger(ValueMap& properties) : super(properties,
	FireTiger::MapKey,
	EntityResources::Enemies_DaemonsHallow_FireTiger_Animations,
	EntityResources::Enemies_DaemonsHallow_FireTiger_Emblem,
	Size(256.0f, 320.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

FireTiger::~FireTiger()
{
}

Vec2 FireTiger::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* FireTiger::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_DaemonsHallow_FireTiger::create();
}
