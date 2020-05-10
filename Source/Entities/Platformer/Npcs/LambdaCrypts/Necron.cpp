#include "Necron.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Necron::MapKey = "necron";

Necron* Necron::deserialize(ValueMap& properties)
{
	Necron* instance = new Necron(properties);

	instance->autorelease();

	return instance;
}

Necron::Necron(ValueMap& properties) : super(properties,
	Necron::MapKey,
	EntityResources::Npcs_LambdaCrypts_Necron_Animations,
	EntityResources::Npcs_LambdaCrypts_Necron_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Necron::~Necron()
{
}

Vec2 Necron::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Necron::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_LambdaCrypts_Necron::create();
}
