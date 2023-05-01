#include "Dudly.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Dudly::MapKey = "dudly";

Dudly* Dudly::deserialize(ValueMap& properties)
{
	Dudly* instance = new Dudly(properties);

	instance->autorelease();

	return instance;
}

Dudly::Dudly(ValueMap& properties) : super(properties,
	Dudly::MapKey,
	EntityResources::Npcs_Transition_Dudly_Animations,
	EntityResources::Npcs_Transition_Dudly_Emblem,
	CSize(112.0f, 160.0f),
	0.9f)
{
}

Dudly::~Dudly()
{
}

Vec2 Dudly::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Dudly::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_Transition_Dudly::create();
}
