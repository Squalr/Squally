#include "KingRedsong.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string KingRedsong::MapKey = "king-redsong";

KingRedsong* KingRedsong::deserialize(ValueMap& properties)
{
	KingRedsong* instance = new KingRedsong(properties);

	instance->autorelease();

	return instance;
}

KingRedsong::KingRedsong(ValueMap& properties) : super(properties,
	KingRedsong::MapKey,
	EntityResources::Npcs_CastleValgrind_KingRedsong_Animations,
	EntityResources::Npcs_CastleValgrind_KingRedsong_Emblem,
	Size(160.0f, 192.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

KingRedsong::~KingRedsong()
{
}

Vec2 KingRedsong::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* KingRedsong::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_CastleValgrind_KingRedsong::create();
}
