#include "TigerMan.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string TigerMan::MapKey = "tiger-man";

TigerMan* TigerMan::deserialize(ValueMap& properties)
{
	TigerMan* instance = new TigerMan(properties);

	instance->autorelease();

	return instance;
}

TigerMan::TigerMan(ValueMap& properties) : super(properties,
	TigerMan::MapKey,
	EntityResources::Enemies_UnderflowRuins_TigerMan_Animations,
	EntityResources::Enemies_UnderflowRuins_TigerMan_Emblem,
	Size(256.0f, 308.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

TigerMan::~TigerMan()
{
}

Vec2 TigerMan::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* TigerMan::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_UnderflowRuins_TigerMan::create();
}
