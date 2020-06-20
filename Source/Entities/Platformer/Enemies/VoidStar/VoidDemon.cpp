#include "VoidDemon.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string VoidDemon::MapKey = "void-demon";

VoidDemon* VoidDemon::deserialize(ValueMap& properties)
{
	VoidDemon* instance = new VoidDemon(properties);

	instance->autorelease();

	return instance;
}

VoidDemon::VoidDemon(ValueMap& properties) : super(properties,
	VoidDemon::MapKey,
	EntityResources::Enemies_VoidStar_VoidDemon_Animations,
	EntityResources::Enemies_VoidStar_VoidDemon_Emblem,
	Size(338.0f, 342.0f),
	0.7f,
	Vec2(0.0f, 0.0f))
{
}

VoidDemon::~VoidDemon()
{
}

Vec2 VoidDemon::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* VoidDemon::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_VoidStar_VoidDemon::create();
}
