#include "Elric.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Elric::MapKey = "elric";

Elric* Elric::deserialize(ValueMap& properties)
{
	Elric* instance = new Elric(properties);

	instance->autorelease();

	return instance;
}

Elric::Elric(ValueMap& properties) : super(properties,
	Elric::MapKey,
	EntityResources::Npcs_LambdaCrypts_Elric_Animations,
	EntityResources::Npcs_LambdaCrypts_Elric_Emblem,
	Size(112.0f, 160.0f),
	1.05f,
	Vec2(0.0f, 0.0f))
{
}

Elric::~Elric()
{
}

Vec2 Elric::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Elric::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_LambdaCrypts_Elric::create();
}
