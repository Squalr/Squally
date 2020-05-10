#include "Brock.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Brock::MapKey = "brock";

Brock* Brock::deserialize(ValueMap& properties)
{
	Brock* instance = new Brock(properties);

	instance->autorelease();

	return instance;
}

Brock::Brock(ValueMap& properties) : super(properties,
	Brock::MapKey,
	EntityResources::Npcs_SeaSharpCaverns_Brock_Animations,
	EntityResources::Npcs_SeaSharpCaverns_Brock_Emblem,
	Size(112.0f, 160.0f),
	1.05f,
	Vec2(0.0f, 0.0f))
{
}

Brock::~Brock()
{
}

Vec2 Brock::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Brock::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_SeaSharpCaverns_Brock::create();
}
