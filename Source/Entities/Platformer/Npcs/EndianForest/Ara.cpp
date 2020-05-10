#include "Ara.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Ara::MapKey = "ara";

Ara* Ara::deserialize(ValueMap& properties)
{
	Ara* instance = new Ara(properties);

	instance->autorelease();

	return instance;
}

Ara::Ara(ValueMap& properties) : super(properties,
	Ara::MapKey,
	EntityResources::Npcs_EndianForest_Ara_Animations,
	EntityResources::Npcs_EndianForest_Ara_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Ara::~Ara()
{
}

Vec2 Ara::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Ara::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_EndianForest_Ara::create();
}
