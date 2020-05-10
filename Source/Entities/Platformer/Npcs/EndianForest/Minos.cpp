#include "Minos.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Minos::MapKey = "minos";

Minos* Minos::deserialize(ValueMap& properties)
{
	Minos* instance = new Minos(properties);

	instance->autorelease();

	return instance;
}

Minos::Minos(ValueMap& properties) : super(properties,
	Minos::MapKey,
	EntityResources::Npcs_EndianForest_Minos_Animations,
	EntityResources::Npcs_EndianForest_Minos_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Minos::~Minos()
{
}

Vec2 Minos::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Minos::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_EndianForest_Minos::create();
}
