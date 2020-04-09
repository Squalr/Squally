#include "Orthrus.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Orthrus::MapKey = "orthrus";

Orthrus* Orthrus::deserialize(ValueMap& properties)
{
	Orthrus* instance = new Orthrus(properties);

	instance->autorelease();

	return instance;
}

Orthrus::Orthrus(ValueMap& properties) : super(properties,
	Orthrus::MapKey,
	EntityResources::Enemies_EndianForest_Orthrus_Animations,
	EntityResources::Enemies_EndianForest_Orthrus_Emblem,
	Size(412.0f, 412.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Orthrus::~Orthrus()
{
}

Vec2 Orthrus::getDialogueOffset()
{
	return Vec2(-32.0f, -280.0f);
}

LocalizedString* Orthrus::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_EndianForest_Orthrus::create();
}
