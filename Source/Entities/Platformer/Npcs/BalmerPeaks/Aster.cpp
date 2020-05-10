#include "Aster.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Aster::MapKey = "aster";

Aster* Aster::deserialize(ValueMap& properties)
{
	Aster* instance = new Aster(properties);

	instance->autorelease();

	return instance;
}

Aster::Aster(ValueMap& properties) : super(properties,
	Aster::MapKey,
	EntityResources::Npcs_BalmerPeaks_Aster_Animations,
	EntityResources::Npcs_BalmerPeaks_Aster_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Aster::~Aster()
{
}

Vec2 Aster::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Aster::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_BalmerPeaks_Aster::create();
}
