#include "Jasper.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Jasper::MapKey = "jasper";

Jasper* Jasper::deserialize(ValueMap& properties)
{
	Jasper* instance = new Jasper(properties);

	instance->autorelease();

	return instance;
}

Jasper::Jasper(ValueMap& properties) : super(properties,
	Jasper::MapKey,
	EntityResources::Npcs_DataMines_Jasper_Animations,
	EntityResources::Npcs_DataMines_Jasper_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Jasper::~Jasper()
{
}

Vec2 Jasper::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Jasper::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_DataMines_Jasper::create();
}
