#include "OrcWarrior.h"

#include "cocos/math/CCGeometry.h"

#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/EntityResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string OrcWarrior::MapKeyOrcWarrior = "orc-warrior";

OrcWarrior* OrcWarrior::deserialize(ValueMap& properties)
{
	OrcWarrior* instance = new OrcWarrior(properties);

	instance->autorelease();

	return instance;
}

OrcWarrior::OrcWarrior(ValueMap& properties) : super(properties,
	OrcWarrior::MapKeyOrcWarrior,
	EntityResources::Enemies_EndianForest_OrcWarrior_Animations,
	EntityResources::Enemies_EndianForest_OrcWarrior_Emblem,
	Size(256.0f, 228.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

OrcWarrior::~OrcWarrior()
{
}

Vec2 OrcWarrior::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* OrcWarrior::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_EndianForest_OrcWarrior::create();
}
