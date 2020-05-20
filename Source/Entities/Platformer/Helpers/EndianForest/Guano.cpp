#include "Guano.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Guano::MapKey = "guano";

Guano* Guano::deserialize(ValueMap& properties)
{
	Guano* instance = new Guano(properties);

	instance->autorelease();

	return instance;
}

Guano::Guano(ValueMap& properties) : super(properties,
	Guano::MapKey,
	EntityResources::Helpers_EndianForest_Guano_Animations,
	EntityResources::Helpers_EndianForest_Guano_Emblem,
	Size(64.0f, 128.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Guano::~Guano()
{
}

Vec2 Guano::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Guano::getEntityName()
{
	return Strings::Platformer_Entities_Names_Helpers_EndianForest_Guano::create();
}
