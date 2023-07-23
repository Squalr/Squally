#include "LavaGolem.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string LavaGolem::MapKey = "lava-golem";

LavaGolem* LavaGolem::deserialize(ValueMap& properties)
{
	LavaGolem* instance = new LavaGolem(properties);

	instance->autorelease();

	return instance;
}

LavaGolem::LavaGolem(ValueMap& properties) : super(properties,
	LavaGolem::MapKey,
	EntityResources::Enemies_FirewallFissure_LavaGolem_Animations,
	EntityResources::Enemies_FirewallFissure_LavaGolem_Emblem,
	CSize(256.0f, 228.0f),
	1.0f)
{
}

LavaGolem::~LavaGolem()
{
}

Vec2 LavaGolem::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* LavaGolem::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_FirewallFissure_LavaGolem::create();
}
