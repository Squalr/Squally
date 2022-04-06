#include "Sarude.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Sarude::MapKey = "sarude";

Sarude* Sarude::deserialize(ValueMap& properties)
{
	Sarude* instance = new Sarude(properties);

	instance->autorelease();

	return instance;
}

Sarude::Sarude(ValueMap& properties) : super(properties,
	Sarude::MapKey,
	EntityResources::Npcs_Mages_Sarude_Animations,
	EntityResources::Npcs_Mages_Sarude_Emblem,
	CSize(112.0f, 160.0f),
	1.05f,
	Vec2(0.0f, 0.0f))
{
}

Sarude::~Sarude()
{
}

Vec2 Sarude::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Sarude::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_DataMines_Sarude::create();
}
