#include "VoidArcher.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string VoidArcher::MapKey = "void-archer";

VoidArcher* VoidArcher::deserialize(ValueMap& properties)
{
	VoidArcher* instance = new VoidArcher(properties);

	instance->autorelease();

	return instance;
}

VoidArcher::VoidArcher(ValueMap& properties) : super(properties,
	VoidArcher::MapKey,
	EntityResources::Enemies_VoidStar_VoidArcher_Animations,
	EntityResources::Enemies_VoidStar_VoidArcher_Emblem,
	Size(196.0f, 348.0f),
	0.65f,
	Vec2(0.0f, 0.0f))
{
}

VoidArcher::~VoidArcher()
{
}

Vec2 VoidArcher::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* VoidArcher::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_VoidStar_VoidArcher::create();
}
