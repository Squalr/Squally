#include "Bancroft.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Bancroft::MapKey = "bancroft";

Bancroft* Bancroft::deserialize(ValueMap& properties)
{
	Bancroft* instance = new Bancroft(properties);

	instance->autorelease();

	return instance;
}

Bancroft::Bancroft(ValueMap& properties) : super(properties,
	Bancroft::MapKey,
	EntityResources::Npcs_VoidStar_Bancroft_Animations,
	EntityResources::Npcs_VoidStar_Bancroft_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Bancroft::~Bancroft()
{
}

Vec2 Bancroft::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Bancroft::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_VoidStar_Bancroft::create();
}
