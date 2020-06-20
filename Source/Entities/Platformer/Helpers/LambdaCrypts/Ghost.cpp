#include "Ghost.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Ghost::MapKey = "ghost";

Ghost* Ghost::deserialize(ValueMap& properties)
{
	Ghost* instance = new Ghost(properties);

	instance->autorelease();

	return instance;
}

Ghost::Ghost(ValueMap& properties) : super(properties,
	Ghost::MapKey,
	EntityResources::Helpers_LambdaCrypts_Ghost_Animations,
	EntityResources::Helpers_LambdaCrypts_Ghost_Emblem,
	Size(224.0f, 440.0f),
	0.3f,
	Vec2(0.0f, 0.0f))
{
}

Ghost::~Ghost()
{
}

Vec2 Ghost::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Ghost::getEntityName()
{
	return Strings::Platformer_Entities_Names_Helpers_LambdaCrypts_Ghost::create();
}
