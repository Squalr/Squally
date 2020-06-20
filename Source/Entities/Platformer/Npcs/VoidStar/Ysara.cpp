#include "Ysara.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Ysara::MapKey = "ysara";

Ysara* Ysara::deserialize(ValueMap& properties)
{
	Ysara* instance = new Ysara(properties);

	instance->autorelease();

	return instance;
}

Ysara::Ysara(ValueMap& properties) : super(properties,
	Ysara::MapKey,
	EntityResources::Npcs_VoidStar_Ysara_Animations,
	EntityResources::Npcs_VoidStar_Ysara_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Ysara::~Ysara()
{
}

Vec2 Ysara::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Ysara::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_VoidStar_Ysara::create();
}
