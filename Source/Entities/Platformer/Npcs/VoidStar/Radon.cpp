#include "Radon.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Radon::MapKey = "radon";

Radon* Radon::deserialize(ValueMap& properties)
{
	Radon* instance = new Radon(properties);

	instance->autorelease();

	return instance;
}

Radon::Radon(ValueMap& properties) : super(properties,
	Radon::MapKey,
	EntityResources::Npcs_VoidStar_Radon_Animations,
	EntityResources::Npcs_VoidStar_Radon_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Radon::~Radon()
{
}

Vec2 Radon::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Radon::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_VoidStar_Radon::create();
}
