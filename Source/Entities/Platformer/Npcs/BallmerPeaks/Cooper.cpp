#include "Cooper.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Cooper::MapKey = "cooper";

Cooper* Cooper::deserialize(ValueMap& properties)
{
	Cooper* instance = new Cooper(properties);

	instance->autorelease();

	return instance;
}

Cooper::Cooper(ValueMap& properties) : super(properties,
	Cooper::MapKey,
	EntityResources::Npcs_BallmerPeaks_Cooper_Animations,
	EntityResources::Npcs_BallmerPeaks_Cooper_Emblem,
	Size(112.0f, 160.0f),
	0.85f,
	Vec2(0.0f, 0.0f))
{
}

Cooper::~Cooper()
{
}

Vec2 Cooper::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Cooper::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_BallmerPeaks_Cooper::create();
}
