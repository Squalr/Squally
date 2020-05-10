#include "Illia.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Illia::MapKey = "illia";

Illia* Illia::deserialize(ValueMap& properties)
{
	Illia* instance = new Illia(properties);

	instance->autorelease();

	return instance;
}

Illia::Illia(ValueMap& properties) : super(properties,
	Illia::MapKey,
	EntityResources::Npcs_VoidStar_Illia_Animations,
	EntityResources::Npcs_VoidStar_Illia_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Illia::~Illia()
{
}

Vec2 Illia::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Illia::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_VoidStar_Illia::create();
}
