#include "Irmik.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Irmik::MapKey = "irmik";

Irmik* Irmik::deserialize(ValueMap& properties)
{
	Irmik* instance = new Irmik(properties);

	instance->autorelease();

	return instance;
}

Irmik::Irmik(ValueMap& properties) : super(properties,
	Irmik::MapKey,
	EntityResources::Npcs_BalmerPeaks_Irmik_Animations,
	EntityResources::Npcs_BalmerPeaks_Irmik_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Irmik::~Irmik()
{
}

Vec2 Irmik::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Irmik::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_BalmerPeaks_Irmik::create();
}
