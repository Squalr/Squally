#include "Snowman.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Snowman::MapKey = "snowman";

Snowman* Snowman::deserialize(ValueMap& properties)
{
	Snowman* instance = new Snowman(properties);

	instance->autorelease();

	return instance;
}

Snowman::Snowman(ValueMap& properties) : super(properties,
	Snowman::MapKey,
	EntityResources::Helpers_BallmerPeaks_Snowman_Animations,
	EntityResources::Helpers_BallmerPeaks_Snowman_Emblem,
	Size(224.0f, 440.0f),
	0.3f,
	Vec2(0.0f, 0.0f))
{
}

Snowman::~Snowman()
{
}

Vec2 Snowman::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Snowman::getEntityName()
{
	return Strings::Platformer_Entities_Names_Helpers_BallmerPeaks_Snowman::create();
}
