#include "Bard.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Bard::MapKey = "bard";

Bard* Bard::deserialize(ValueMap& properties)
{
	Bard* instance = new Bard(properties);

	instance->autorelease();

	return instance;
}

Bard::Bard(ValueMap& properties) : super(properties,
	Bard::MapKey,
	EntityResources::Npcs_EndianForest_Bard_Animations,
	EntityResources::Npcs_EndianForest_Bard_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Bard::~Bard()
{
}

Vec2 Bard::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Bard::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_EndianForest_Bard::create();
}
