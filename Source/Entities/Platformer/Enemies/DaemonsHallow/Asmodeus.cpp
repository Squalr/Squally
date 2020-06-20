#include "Asmodeus.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Asmodeus::MapKey = "asmodeus";

Asmodeus* Asmodeus::deserialize(ValueMap& properties)
{
	Asmodeus* instance = new Asmodeus(properties);

	instance->autorelease();

	return instance;
}

Asmodeus::Asmodeus(ValueMap& properties) : super(properties,
	Asmodeus::MapKey,
	EntityResources::Enemies_DaemonsHallow_Asmodeus_Animations,
	EntityResources::Enemies_DaemonsHallow_Asmodeus_Emblem,
	Size(480.0f, 480.0f),
	0.8f,
	Vec2(0.0f, 0.0f))
{
}

Asmodeus::~Asmodeus()
{
}

Vec2 Asmodeus::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Asmodeus::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_DaemonsHallow_Asmodeus::create();
}
