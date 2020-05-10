#include "CritterDemon.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string CritterDemon::MapKey = "critter-demon";

CritterDemon* CritterDemon::deserialize(ValueMap& properties)
{
	CritterDemon* instance = new CritterDemon(properties);

	instance->autorelease();

	return instance;
}

CritterDemon::CritterDemon(ValueMap& properties) : super(properties,
	CritterDemon::MapKey,
	EntityResources::Helpers_DaemonsHallow_CritterDemon_Animations,
	EntityResources::Helpers_DaemonsHallow_CritterDemon_Emblem,
	Size(188.0f, 160.0f),
	0.7f,
	Vec2(0.0f, 0.0f))
{
}

CritterDemon::~CritterDemon()
{
}

Vec2 CritterDemon::getDialogueOffset()
{
	return Vec2(-48.0f, -112.0f);
}

LocalizedString* CritterDemon::getEntityName()
{
	return Strings::Platformer_Entities_Names_Helpers_DaemonsHallow_CritterDemon::create();
}
