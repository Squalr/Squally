#include "Geryon.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Geryon::MapKey = "geryon";

Geryon* Geryon::deserialize(ValueMap& properties)
{
	Geryon* instance = new Geryon(properties);

	instance->autorelease();

	return instance;
}

Geryon::Geryon(ValueMap& properties) : super(properties,
	Geryon::MapKey,
	EntityResources::Npcs_UnderflowRuins_Geryon_Animations,
	EntityResources::Npcs_UnderflowRuins_Geryon_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Geryon::~Geryon()
{
}

Vec2 Geryon::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Geryon::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_UnderflowRuins_Geryon::create();
}
