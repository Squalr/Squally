#include "TikiGolem.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string TikiGolem::MapKey = "tiki-golem";

TikiGolem* TikiGolem::deserialize(ValueMap& properties)
{
	TikiGolem* instance = new TikiGolem(properties);

	instance->autorelease();

	return instance;
}

TikiGolem::TikiGolem(ValueMap& properties) : super(properties,
	TikiGolem::MapKey,
	EntityResources::Enemies_SeaSharpCaverns_TikiGolem_Animations,
	EntityResources::Enemies_SeaSharpCaverns_TikiGolem_Emblem,
	Size(284.0f, 256.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

TikiGolem::~TikiGolem()
{
}

Vec2 TikiGolem::getDialogueOffset()
{
	return Vec2(-32.0f, -128.0f);
}

LocalizedString* TikiGolem::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_SeaSharpCaverns_TikiGolem::create();
}
