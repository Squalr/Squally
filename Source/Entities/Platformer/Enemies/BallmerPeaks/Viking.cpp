#include "Viking.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Viking::MapKey = "viking";

Viking* Viking::deserialize(ValueMap& properties)
{
	Viking* instance = new Viking(properties);

	instance->autorelease();

	return instance;
}

Viking::Viking(ValueMap& properties) : super(properties,
	Viking::MapKey,
	EntityResources::Enemies_BallmerPeaks_Viking_Animations,
	EntityResources::Enemies_BallmerPeaks_Viking_Emblem,
	Size(980.0f, 1200.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Viking::~Viking()
{
}

Vec2 Viking::getDialogueOffset()
{
	return Vec2(-32.0f, -144.0f);
}

LocalizedString* Viking::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_BallmerPeaks_Viking::create();
}
