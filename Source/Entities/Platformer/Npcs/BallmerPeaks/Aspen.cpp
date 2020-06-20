#include "Aspen.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Aspen::MapKey = "aspen";

Aspen* Aspen::deserialize(ValueMap& properties)
{
	Aspen* instance = new Aspen(properties);

	instance->autorelease();

	return instance;
}

Aspen::Aspen(ValueMap& properties) : super(properties,
	Aspen::MapKey,
	EntityResources::Npcs_BallmerPeaks_Aspen_Animations,
	EntityResources::Npcs_BallmerPeaks_Aspen_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Aspen::~Aspen()
{
}

Vec2 Aspen::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Aspen::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_BallmerPeaks_Aspen::create();
}
