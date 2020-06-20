#include "Theldar.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Theldar::MapKey = "theldar";

Theldar* Theldar::deserialize(ValueMap& properties)
{
	Theldar* instance = new Theldar(properties);

	instance->autorelease();

	return instance;
}

Theldar::Theldar(ValueMap& properties) : super(properties,
	Theldar::MapKey,
	EntityResources::Npcs_BallmerPeaks_Theldar_Animations,
	EntityResources::Npcs_BallmerPeaks_Theldar_Emblem,
	Size(112.0f, 160.0f),
	0.9f,
	Vec2(0.0f, 0.0f))
{
}

Theldar::~Theldar()
{
}

Vec2 Theldar::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Theldar::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_BallmerPeaks_Theldar::create();
}
