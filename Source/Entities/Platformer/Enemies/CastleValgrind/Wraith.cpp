#include "Wraith.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Wraith::MapKey = "wraith";

Wraith* Wraith::deserialize(ValueMap& properties)
{
	Wraith* instance = new Wraith(properties);

	instance->autorelease();

	return instance;
}

Wraith::Wraith(ValueMap& properties) : super(properties,
	Wraith::MapKey,
	EntityResources::Enemies_CastleValgrind_Wraith_Animations,
	EntityResources::Enemies_CastleValgrind_Wraith_Emblem,
	Size(142.0f, 400.0f),
	0.6f,
	Vec2(0.0f, 0.0f))
{
}

Wraith::~Wraith()
{
}

Vec2 Wraith::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Wraith::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_CastleValgrind_Wraith::create();
}
