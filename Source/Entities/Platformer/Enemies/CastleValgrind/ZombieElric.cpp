#include "ZombieElric.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string ZombieElric::MapKey = "zombie-elric";

ZombieElric* ZombieElric::deserialize(ValueMap& properties)
{
	ZombieElric* instance = new ZombieElric(properties);

	instance->autorelease();

	return instance;
}

ZombieElric::ZombieElric(ValueMap& properties) : super(properties,
	ZombieElric::MapKey,
	EntityResources::Enemies_CastleValgrind_ZombieElric_Animations,
	EntityResources::Enemies_CastleValgrind_ZombieElric_Emblem,
	Size(114.0f, 208.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

ZombieElric::~ZombieElric()
{
}

Vec2 ZombieElric::getDialogueOffset()
{
	return Vec2(-16.0f, -112.0f);
}

LocalizedString* ZombieElric::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_CastleValgrind_ZombieElric::create();
}
