#include "Medusa.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Medusa::MapKey = "medusa";

Medusa* Medusa::deserialize(ValueMap& properties)
{
	Medusa* instance = new Medusa(properties);

	instance->autorelease();

	return instance;
}

Medusa::Medusa(ValueMap& properties) : super(properties,
	Medusa::MapKey,
	EntityResources::Enemies_UnderflowRuins_Medusa_Animations,
	EntityResources::Enemies_UnderflowRuins_Medusa_Emblem,
	Size(224.0f, 304.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Medusa::~Medusa()
{
}

Vec2 Medusa::getDialogueOffset()
{
	return Vec2(-32.0f, -196.0f);
}

LocalizedString* Medusa::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_UnderflowRuins_Medusa::create();
}
