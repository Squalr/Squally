#include "Chiron.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Chiron::MapKey = "chiron";

Chiron* Chiron::deserialize(ValueMap& properties)
{
	Chiron* instance = new Chiron(properties);

	instance->autorelease();

	return instance;
}

Chiron::Chiron(ValueMap& properties) : super(properties,
	Chiron::MapKey,
	EntityResources::Npcs_EndianForest_Chiron_Animations,
	EntityResources::Npcs_EndianForest_Chiron_Emblem,
	Size(160.0f, 224.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Chiron::~Chiron()
{
}

Vec2 Chiron::getDialogueOffset()
{
	return Vec2(-48.0f, -32.0f);
}

LocalizedString* Chiron::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_EndianForest_Chiron::create();
}
