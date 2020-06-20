#include "Leopold.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Leopold::MapKey = "leopold";

Leopold* Leopold::deserialize(ValueMap& properties)
{
	Leopold* instance = new Leopold(properties);

	instance->autorelease();

	return instance;
}

Leopold::Leopold(ValueMap& properties) : super(properties,
	Leopold::MapKey,
	EntityResources::Npcs_CastleValgrind_Leopold_Animations,
	EntityResources::Npcs_CastleValgrind_Leopold_Emblem,
	Size(112.0f, 160.0f),
	0.95f,
	Vec2(0.0f, 0.0f))
{
}

Leopold::~Leopold()
{
}

Vec2 Leopold::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Leopold::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_CastleValgrind_Leopold::create();
}
