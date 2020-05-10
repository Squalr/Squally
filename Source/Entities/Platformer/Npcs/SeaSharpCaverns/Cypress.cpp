#include "Cypress.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Cypress::MapKey = "cypress";

Cypress* Cypress::deserialize(ValueMap& properties)
{
	Cypress* instance = new Cypress(properties);

	instance->autorelease();

	return instance;
}

Cypress::Cypress(ValueMap& properties) : super(properties,
	Cypress::MapKey,
	EntityResources::Npcs_SeaSharpCaverns_Cypress_Animations,
	EntityResources::Npcs_SeaSharpCaverns_Cypress_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Cypress::~Cypress()
{
}

Vec2 Cypress::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Cypress::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_SeaSharpCaverns_Cypress::create();
}
