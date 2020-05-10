#include "DarkTiger.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string DarkTiger::MapKey = "dark-tiger";

DarkTiger* DarkTiger::deserialize(ValueMap& properties)
{
	DarkTiger* instance = new DarkTiger(properties);

	instance->autorelease();

	return instance;
}

DarkTiger::DarkTiger(ValueMap& properties) : super(properties,
	DarkTiger::MapKey,
	EntityResources::Enemies_VoidStar_DarkTiger_Animations,
	EntityResources::Enemies_VoidStar_DarkTiger_Emblem,
	Size(256.0f, 248.0f),
	0.9f,
	Vec2(0.0f, 0.0f))
{
}

DarkTiger::~DarkTiger()
{
}

Vec2 DarkTiger::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* DarkTiger::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_VoidStar_DarkTiger::create();
}
