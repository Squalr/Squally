#include "Ursula.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Ursula::MapKey = "ursula";

Ursula* Ursula::deserialize(ValueMap& properties)
{
	Ursula* instance = new Ursula(properties);

	instance->autorelease();

	return instance;
}

Ursula::Ursula(ValueMap& properties) : super(properties,
	Ursula::MapKey,
	EntityResources::Npcs_LambdaCrypts_Ursula_Animations,
	EntityResources::Npcs_LambdaCrypts_Ursula_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Ursula::~Ursula()
{
}

Vec2 Ursula::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Ursula::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_LambdaCrypts_Ursula::create();
}
