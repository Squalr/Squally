#include "Alder.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Alder::MapKey = "alder";

Alder* Alder::deserialize(ValueMap& properties)
{
	Alder* instance = new Alder(properties);

	instance->autorelease();

	return instance;
}

Alder::Alder(ValueMap& properties) : super(properties,
	Alder::MapKey,
	EntityResources::Npcs_DataMines_Alder_Animations,
	EntityResources::Npcs_DataMines_Alder_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Alder::~Alder()
{
}

Vec2 Alder::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Alder::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_DataMines_Alder::create();
}
