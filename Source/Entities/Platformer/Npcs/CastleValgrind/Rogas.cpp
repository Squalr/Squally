#include "Rogas.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Rogas::MapKey = "rogas";

Rogas* Rogas::deserialize(ValueMap& properties)
{
	Rogas* instance = new Rogas(properties);

	instance->autorelease();

	return instance;
}

Rogas::Rogas(ValueMap& properties) : super(properties,
	Rogas::MapKey,
	EntityResources::Npcs_CastleValgrind_Rogas_Animations,
	EntityResources::Npcs_CastleValgrind_Rogas_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Rogas::~Rogas()
{
}

Vec2 Rogas::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Rogas::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_CastleValgrind_Rogas::create();
}
