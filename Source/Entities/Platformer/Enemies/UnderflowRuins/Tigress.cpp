#include "Tigress.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Tigress::MapKey = "tigress";

Tigress* Tigress::deserialize(ValueMap& properties)
{
	Tigress* instance = new Tigress(properties);

	instance->autorelease();

	return instance;
}

Tigress::Tigress(ValueMap& properties) : super(properties,
	Tigress::MapKey,
	EntityResources::Enemies_UnderflowRuins_Tigress_Animations,
	EntityResources::Enemies_UnderflowRuins_Tigress_Emblem,
	Size(128.0f, 256.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Tigress::~Tigress()
{
}

Vec2 Tigress::getDialogueOffset()
{
	return Vec2(-16.0f, -160.0f);
}

LocalizedString* Tigress::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_UnderflowRuins_Tigress::create();
}
