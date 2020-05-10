#include "DemonWarrior.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string DemonWarrior::MapKey = "demon-warrior";

DemonWarrior* DemonWarrior::deserialize(ValueMap& properties)
{
	DemonWarrior* instance = new DemonWarrior(properties);

	instance->autorelease();

	return instance;
}

DemonWarrior::DemonWarrior(ValueMap& properties) : super(properties,
	DemonWarrior::MapKey,
	EntityResources::Enemies_DaemonsHallow_DemonWarrior_Animations,
	EntityResources::Enemies_DaemonsHallow_DemonWarrior_Emblem,
	Size(320.0f, 372.0f),
	0.7f,
	Vec2(0.0f, 0.0f))
{
}

DemonWarrior::~DemonWarrior()
{
}

Vec2 DemonWarrior::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* DemonWarrior::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_DaemonsHallow_DemonWarrior::create();
}
