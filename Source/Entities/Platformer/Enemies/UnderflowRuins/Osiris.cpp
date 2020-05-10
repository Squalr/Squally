#include "Osiris.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Osiris::MapKey = "osiris";

Osiris* Osiris::deserialize(ValueMap& properties)
{
	Osiris* instance = new Osiris(properties);

	instance->autorelease();

	return instance;
}

Osiris::Osiris(ValueMap& properties) : super(properties,
	Osiris::MapKey,
	EntityResources::Enemies_UnderflowRuins_Osiris_Animations,
	EntityResources::Enemies_UnderflowRuins_Osiris_Emblem,
	Size(324.0f, 316.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Osiris::~Osiris()
{
}

Vec2 Osiris::getDialogueOffset()
{
	return Vec2(-32.0f, -212.0f);
}

LocalizedString* Osiris::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_UnderflowRuins_Osiris::create();
}
