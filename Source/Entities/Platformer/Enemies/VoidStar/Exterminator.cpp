#include "Exterminator.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Exterminator::MapKey = "exterminator";

Exterminator* Exterminator::deserialize(ValueMap& properties)
{
	Exterminator* instance = new Exterminator(properties);

	instance->autorelease();

	return instance;
}

Exterminator::Exterminator(ValueMap& properties) : super(properties,
	Exterminator::MapKey,
	EntityResources::Enemies_VoidStar_Exterminator_Animations,
	EntityResources::Enemies_VoidStar_Exterminator_Emblem,
	Size(320.0f, 278.0f),
	0.9f,
	Vec2(0.0f, 0.0f))
{
}

Exterminator::~Exterminator()
{
}

Vec2 Exterminator::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Exterminator::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_VoidStar_Exterminator::create();
}
