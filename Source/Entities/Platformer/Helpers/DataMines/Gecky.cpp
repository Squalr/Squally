#include "Gecky.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Gecky::MapKey = "gecky";

Gecky* Gecky::deserialize(ValueMap& properties)
{
	Gecky* instance = new Gecky(properties);

	instance->autorelease();

	return instance;
}

Gecky::Gecky(ValueMap& properties) : super(properties,
	Gecky::MapKey,
	EntityResources::Helpers_DataMines_Gecky_Animations,
	EntityResources::Helpers_DataMines_Gecky_Emblem,
	Size(64.0f, 128.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Gecky::~Gecky()
{
}

Vec2 Gecky::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Gecky::getEntityName()
{
	return Strings::Platformer_Entities_Names_Helpers_DataMines_Gecky::create();
}
