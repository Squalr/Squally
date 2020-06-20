#include "Marcel.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Marcel::MapKey = "marcel";

Marcel* Marcel::deserialize(ValueMap& properties)
{
	Marcel* instance = new Marcel(properties);

	instance->autorelease();

	return instance;
}

Marcel::Marcel(ValueMap& properties) : super(properties,
	Marcel::MapKey,
	EntityResources::Npcs_EndianForest_Marcel_Animations,
	EntityResources::Npcs_EndianForest_Marcel_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Marcel::~Marcel()
{
}

Vec2 Marcel::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Marcel::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_EndianForest_Marcel::create();
}
