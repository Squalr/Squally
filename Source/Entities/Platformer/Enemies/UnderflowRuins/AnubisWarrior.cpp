#include "AnubisWarrior.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string AnubisWarrior::MapKey = "anubis-warrior";

AnubisWarrior* AnubisWarrior::deserialize(ValueMap& properties)
{
	AnubisWarrior* instance = new AnubisWarrior(properties);

	instance->autorelease();

	return instance;
}

AnubisWarrior::AnubisWarrior(ValueMap& properties) : super(properties,
	AnubisWarrior::MapKey,
	EntityResources::Enemies_UnderflowRuins_AnubisWarrior_Animations,
	EntityResources::Enemies_UnderflowRuins_AnubisWarrior_Emblem,
	Size(256.0f, 292.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

AnubisWarrior::~AnubisWarrior()
{
}

Vec2 AnubisWarrior::getDialogueOffset()
{
	return Vec2(-32.0f, -196.0f);
}

LocalizedString* AnubisWarrior::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_UnderflowRuins_AnubisWarrior::create();
}
