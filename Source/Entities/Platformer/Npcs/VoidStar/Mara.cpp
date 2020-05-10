#include "Mara.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Mara::MapKey = "mara";

Mara* Mara::deserialize(ValueMap& properties)
{
	Mara* instance = new Mara(properties);

	instance->autorelease();

	return instance;
}

Mara::Mara(ValueMap& properties) : super(properties,
	Mara::MapKey,
	EntityResources::Npcs_VoidStar_Mara_Animations,
	EntityResources::Npcs_VoidStar_Mara_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Mara::~Mara()
{
}

Vec2 Mara::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Mara::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_VoidStar_Mara::create();
}
