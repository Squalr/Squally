#include "Raka.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Raka::MapKey = "raka";

Raka* Raka::deserialize(ValueMap& properties)
{
	Raka* instance = new Raka(properties);

	instance->autorelease();

	return instance;
}

Raka::Raka(ValueMap& properties) : super(properties,
	Raka::MapKey,
	EntityResources::Npcs_SeaSharpCaverns_Raka_Animations,
	EntityResources::Npcs_SeaSharpCaverns_Raka_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Raka::~Raka()
{
}

Vec2 Raka::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Raka::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_SeaSharpCaverns_Raka::create();
}
