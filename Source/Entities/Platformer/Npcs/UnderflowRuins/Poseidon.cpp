#include "Poseidon.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Poseidon::MapKey = "poseidon";

Poseidon* Poseidon::deserialize(ValueMap& properties)
{
	Poseidon* instance = new Poseidon(properties);

	instance->autorelease();

	return instance;
}

Poseidon::Poseidon(ValueMap& properties) : super(properties,
	Poseidon::MapKey,
	EntityResources::Npcs_UnderflowRuins_Poseidon_Animations,
	EntityResources::Npcs_UnderflowRuins_Poseidon_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Poseidon::~Poseidon()
{
}

Vec2 Poseidon::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Poseidon::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_UnderflowRuins_Poseidon::create();
}
