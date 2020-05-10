#include "Elriel.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Elriel::MapKey = "elriel";

Elriel* Elriel::deserialize(ValueMap& properties)
{
	Elriel* instance = new Elriel(properties);

	instance->autorelease();

	return instance;
}

Elriel::Elriel(ValueMap& properties) : super(properties,
	Elriel::MapKey,
	EntityResources::Npcs_EndianForest_Elriel_Animations,
	EntityResources::Npcs_EndianForest_Elriel_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Elriel::~Elriel()
{
}

Vec2 Elriel::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Elriel::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_EndianForest_Elriel::create();
}
