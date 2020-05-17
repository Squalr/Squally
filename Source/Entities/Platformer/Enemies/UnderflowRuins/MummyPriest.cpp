#include "MummyPriest.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string MummyPriest::MapKey = "mummy-priest";

MummyPriest* MummyPriest::deserialize(ValueMap& properties)
{
	MummyPriest* instance = new MummyPriest(properties);

	instance->autorelease();

	return instance;
}

MummyPriest::MummyPriest(ValueMap& properties) : super(properties,
	MummyPriest::MapKey,
	EntityResources::Enemies_UnderflowRuins_MummyPriest_Animations,
	EntityResources::Enemies_UnderflowRuins_MummyPriest_Emblem,
	Size(128.0f, 256.0f),
	0.85f,
	Vec2(0.0f, 0.0f))
{
}

MummyPriest::~MummyPriest()
{
}

Vec2 MummyPriest::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* MummyPriest::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_UnderflowRuins_MummyPriest::create();
}
