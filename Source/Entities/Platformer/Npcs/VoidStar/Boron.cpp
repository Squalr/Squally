#include "Boron.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Boron::MapKey = "boron";

Boron* Boron::deserialize(ValueMap& properties)
{
	Boron* instance = new Boron(properties);

	instance->autorelease();

	return instance;
}

Boron::Boron(ValueMap& properties) : super(properties,
	Boron::MapKey,
	EntityResources::Npcs_VoidStar_Boron_Animations,
	EntityResources::Npcs_VoidStar_Boron_Emblem,
	CSize(112.0f, 160.0f),
	1.0f)
{
}

Boron::~Boron()
{
}

Vec2 Boron::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Boron::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_VoidStar_Boron::create();
}
