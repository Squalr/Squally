#include "Shen.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Shen::MapKey = "shen";

Shen* Shen::deserialize(ValueMap& properties)
{
	Shen* instance = new Shen(properties);

	instance->autorelease();

	return instance;
}

Shen::Shen(ValueMap& properties) : super(properties,
	Shen::MapKey,
	EntityResources::Npcs_SeaSharpCaverns_Shen_Animations,
	EntityResources::Npcs_SeaSharpCaverns_Shen_Emblem,
	Size(112.0f, 160.0f),
	1.05f,
	Vec2(0.0f, 0.0f))
{
}

Shen::~Shen()
{
}

Vec2 Shen::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Shen::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_SeaSharpCaverns_Shen::create();
}
