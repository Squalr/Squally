#include "Professor.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Professor::MapKey = "professor";

Professor* Professor::deserialize(ValueMap& properties)
{
	Professor* instance = new Professor(properties);

	instance->autorelease();

	return instance;
}

Professor::Professor(ValueMap& properties) : super(properties,
	Professor::MapKey,
	EntityResources::Helpers_VoidStar_Professor_Animations,
	EntityResources::Helpers_VoidStar_Professor_Emblem,
	Size(224.0f, 440.0f),
	0.3f,
	Vec2(0.0f, 0.0f))
{
}

Professor::~Professor()
{
}

Vec2 Professor::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Professor::getEntityName()
{
	return Strings::Platformer_Entities_Names_Helpers_VoidStar_Professor::create();
}
