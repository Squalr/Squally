#include "MummyWarrior.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string MummyWarrior::MapKey = "mummy-warrior";

MummyWarrior* MummyWarrior::deserialize(ValueMap& properties)
{
	MummyWarrior* instance = new MummyWarrior(properties);

	instance->autorelease();

	return instance;
}

MummyWarrior::MummyWarrior(ValueMap& properties) : super(properties,
	MummyWarrior::MapKey,
	EntityResources::Enemies_UnderflowRuins_MummyWarrior_Animations,
	EntityResources::Enemies_UnderflowRuins_MummyWarrior_Emblem,
	Size(128.0f, 256.0f),
	0.85f,
	Vec2(0.0f, 0.0f))
{
}

MummyWarrior::~MummyWarrior()
{
}

Vec2 MummyWarrior::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* MummyWarrior::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_UnderflowRuins_MummyWarrior::create();
}
