#include "Gull.h"

#include "cocos/math/CCGeometry.h"

#include "Engine/Animations/SmartAnimationNode.h"

#include "Resources/EntityResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Gull::MapKey = "gull";

Gull* Gull::deserialize(ValueMap& properties)
{
	Gull* instance = new Gull(properties);

	instance->autorelease();

	return instance;
}

Gull::Gull(ValueMap& properties) : super(properties,
	Gull::MapKey,
	EntityResources::Misc_UnderflowRuins_Gull_Animations,
	EntityResources::Misc_UnderflowRuins_Gull_Emblem,
	CSize(96.0f, 160.0f),
	0.8f,
	Vec2(0.0f, 0.0f))
{
	this->animationNode->setScaleX(-this->getScale());
}

Gull::~Gull()
{
}

Vec2 Gull::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Gull::getEntityName()
{
	return Strings::Platformer_Entities_Names_Critters_Gull::create();
}
