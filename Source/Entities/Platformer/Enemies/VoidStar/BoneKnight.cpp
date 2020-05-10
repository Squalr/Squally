#include "BoneKnight.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string BoneKnight::MapKey = "bone-knight";

BoneKnight* BoneKnight::deserialize(ValueMap& properties)
{
	BoneKnight* instance = new BoneKnight(properties);

	instance->autorelease();

	return instance;
}

BoneKnight::BoneKnight(ValueMap& properties) : super(properties,
	BoneKnight::MapKey,
	EntityResources::Enemies_VoidStar_BoneKnight_Animations,
	EntityResources::Enemies_VoidStar_BoneKnight_Emblem,
	Size(540.0f, 340.0f),
	1.0f,
	Vec2(-64.0f, 0.0f))
{
}

BoneKnight::~BoneKnight()
{
}

Vec2 BoneKnight::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* BoneKnight::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_VoidStar_BoneKnight::create();
}
