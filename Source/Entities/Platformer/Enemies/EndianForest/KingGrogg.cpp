#include "KingGrogg.h"

#include "cocos/math/CCGeometry.h"

#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/EntityResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string KingGrogg::MapKeyKingGrogg = "king-grogg";

KingGrogg* KingGrogg::deserialize(ValueMap& properties)
{
	KingGrogg* instance = new KingGrogg(properties);

	instance->autorelease();

	return instance;
}

KingGrogg::KingGrogg(ValueMap& properties) : super(properties,
	KingGrogg::MapKeyKingGrogg,
	EntityResources::Enemies_EndianForest_KingGrogg_Animations,
	EntityResources::Enemies_EndianForest_KingGrogg_Emblem,
	Size(412.0f, 412.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = KingGrogg::getHexusOpponentData();
}

KingGrogg::~KingGrogg()
{
}

Vec2 KingGrogg::getDialogueOffset()
{
	return Vec2(-32.0f, -280.0f);
}

LocalizedString* KingGrogg::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_EndianForest_KingGrogg::create();
}
