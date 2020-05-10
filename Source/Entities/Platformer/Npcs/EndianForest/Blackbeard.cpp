#include "Blackbeard.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Blackbeard::MapKey = "blackbeard";

Blackbeard* Blackbeard::deserialize(ValueMap& properties)
{
	Blackbeard* instance = new Blackbeard(properties);

	instance->autorelease();

	return instance;
}

Blackbeard::Blackbeard(ValueMap& properties) : super(properties,
	Blackbeard::MapKey,
	EntityResources::Npcs_EndianForest_Blackbeard_Animations,
	EntityResources::Npcs_EndianForest_Blackbeard_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Blackbeard::~Blackbeard()
{
}

Vec2 Blackbeard::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Blackbeard::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_EndianForest_Blackbeard::create();
}
