#include "KingRedsongSlime.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string KingRedsongSlime::MapKey = "king-redsong-slime";

KingRedsongSlime* KingRedsongSlime::deserialize(ValueMap& properties)
{
	KingRedsongSlime* instance = new KingRedsongSlime(properties);

	instance->autorelease();

	return instance;
}

KingRedsongSlime::KingRedsongSlime(ValueMap& properties) : super(properties,
	KingRedsongSlime::MapKey,
	EntityResources::Npcs_CastleValgrind_KingRedsongSlime_Animations,
	EntityResources::Npcs_CastleValgrind_KingRedsongSlime_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

KingRedsongSlime::~KingRedsongSlime()
{
}

Vec2 KingRedsongSlime::getDialogueOffset()
{
	return Vec2(-32.0f, -96.0f);
}

LocalizedString* KingRedsongSlime::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_CastleValgrind_KingRedsong::create();
}
