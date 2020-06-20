#include "Werewolf.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Werewolf::MapKey = "werewolf";

Werewolf* Werewolf::deserialize(ValueMap& properties)
{
	Werewolf* instance = new Werewolf(properties);

	instance->autorelease();

	return instance;
}

Werewolf::Werewolf(ValueMap& properties) : super(properties,
	Werewolf::MapKey,
	EntityResources::Enemies_CastleValgrind_Werewolf_Animations,
	EntityResources::Enemies_CastleValgrind_Werewolf_Emblem,
	Size(196.0f, 512.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Werewolf::~Werewolf()
{
}

Vec2 Werewolf::getDialogueOffset()
{
	return Vec2(-32.0f, -160.0f);
}

LocalizedString* Werewolf::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_CastleValgrind_Werewolf::create();
}
