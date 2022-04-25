#include "DemonArcher.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string DemonArcher::MapKey = "demon-archer";

DemonArcher* DemonArcher::deserialize(ValueMap& properties)
{
	DemonArcher* instance = new DemonArcher(properties);

	instance->autorelease();

	return instance;
}

DemonArcher::DemonArcher(ValueMap& properties) : super(properties,
	DemonArcher::MapKey,
	EntityResources::Enemies_DaemonsHallow_DemonArcher_Animations,
	EntityResources::Enemies_DaemonsHallow_DemonArcher_Emblem,
	CSize(196.0f, 348.0f),
	0.65f,
	Vec2(0.0f, 0.0f))
{
}

DemonArcher::~DemonArcher()
{
}

Vec2 DemonArcher::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* DemonArcher::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_VoidStar_DemonArcher::create();
}
