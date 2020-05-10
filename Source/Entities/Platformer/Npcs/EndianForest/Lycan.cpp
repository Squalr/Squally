#include "Lycan.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Lycan::MapKey = "lycan";

Lycan* Lycan::deserialize(ValueMap& properties)
{
	Lycan* instance = new Lycan(properties);

	instance->autorelease();

	return instance;
}

Lycan::Lycan(ValueMap& properties) : super(properties,
	Lycan::MapKey,
	EntityResources::Npcs_EndianForest_Lycan_Animations,
	EntityResources::Npcs_EndianForest_Lycan_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Lycan::~Lycan()
{
}

Vec2 Lycan::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Lycan::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_EndianForest_Lycan::create();
}
