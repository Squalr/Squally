#include "Thion.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Thion::MapKey = "thion";

Thion* Thion::deserialize(ValueMap& properties)
{
	Thion* instance = new Thion(properties);

	instance->autorelease();

	return instance;
}

Thion::Thion(ValueMap& properties) : super(properties,
	Thion::MapKey,
	EntityResources::Npcs_LambdaCrypts_Thion_Animations,
	EntityResources::Npcs_LambdaCrypts_Thion_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Thion::~Thion()
{
}

Vec2 Thion::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Thion::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_LambdaCrypts_Thion::create();
}
