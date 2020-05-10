#include "Piper.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Piper::MapKey = "piper";

Piper* Piper::deserialize(ValueMap& properties)
{
	Piper* instance = new Piper(properties);

	instance->autorelease();

	return instance;
}

Piper::Piper(ValueMap& properties) : super(properties,
	Piper::MapKey,
	EntityResources::Npcs_VoidStar_Piper_Animations,
	EntityResources::Npcs_VoidStar_Piper_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Piper::~Piper()
{
}

Vec2 Piper::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Piper::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_VoidStar_Piper::create();
}
