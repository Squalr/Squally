#include "Jack.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Jack::MapKey = "jack";

Jack* Jack::deserialize(ValueMap& properties)
{
	Jack* instance = new Jack(properties);

	instance->autorelease();

	return instance;
}

Jack::Jack(ValueMap& properties) : super(properties,
	Jack::MapKey,
	EntityResources::Enemies_CastleValgrind_Jack_Animations,
	EntityResources::Enemies_CastleValgrind_Jack_Emblem,
	Size(432.0f, 768.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Jack::~Jack()
{
}

Vec2 Jack::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Jack::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_CastleValgrind_Jack::create();
}
