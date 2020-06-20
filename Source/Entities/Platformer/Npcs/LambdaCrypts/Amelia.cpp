#include "Amelia.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Amelia::MapKey = "amelia";

Amelia* Amelia::deserialize(ValueMap& properties)
{
	Amelia* instance = new Amelia(properties);

	instance->autorelease();

	return instance;
}

Amelia::Amelia(ValueMap& properties) : super(properties,
	Amelia::MapKey,
	EntityResources::Npcs_LambdaCrypts_Amelia_Animations,
	EntityResources::Npcs_LambdaCrypts_Amelia_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Amelia::~Amelia()
{
}

Vec2 Amelia::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Amelia::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_LambdaCrypts_Amelia::create();
}
