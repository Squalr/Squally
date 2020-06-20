#include "Azmus.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Azmus::MapKey = "azmus";

Azmus* Azmus::deserialize(ValueMap& properties)
{
	Azmus* instance = new Azmus(properties);

	instance->autorelease();

	return instance;
}

Azmus::Azmus(ValueMap& properties) : super(properties,
	Azmus::MapKey,
	EntityResources::Npcs_LambdaCrypts_Azmus_Animations,
	EntityResources::Npcs_LambdaCrypts_Azmus_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Azmus::~Azmus()
{
}

Vec2 Azmus::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Azmus::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_LambdaCrypts_Azmus::create();
}
