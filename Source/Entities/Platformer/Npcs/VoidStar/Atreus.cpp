#include "Atreus.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Atreus::MapKey = "atreus";

Atreus* Atreus::deserialize(ValueMap& properties)
{
	Atreus* instance = new Atreus(properties);

	instance->autorelease();

	return instance;
}

Atreus::Atreus(ValueMap& properties) : super(properties,
	Atreus::MapKey,
	EntityResources::Npcs_VoidStar_Atreus_Animations,
	EntityResources::Npcs_VoidStar_Atreus_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Atreus::~Atreus()
{
}

Vec2 Atreus::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Atreus::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_VoidStar_Atreus::create();
}
