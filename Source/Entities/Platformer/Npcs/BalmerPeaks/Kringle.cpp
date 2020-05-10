#include "Kringle.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Kringle::MapKey = "kringle";

Kringle* Kringle::deserialize(ValueMap& properties)
{
	Kringle* instance = new Kringle(properties);

	instance->autorelease();

	return instance;
}

Kringle::Kringle(ValueMap& properties) : super(properties,
	Kringle::MapKey,
	EntityResources::Npcs_BalmerPeaks_Kringle_Animations,
	EntityResources::Npcs_BalmerPeaks_Kringle_Emblem,
	Size(112.0f, 160.0f),
	0.85f,
	Vec2(0.0f, 0.0f))
{
}

Kringle::~Kringle()
{
}

Vec2 Kringle::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Kringle::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_BalmerPeaks_Kringle::create();
}
