#include "Centaur.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Centaur::MapKey = "centaur";

Centaur* Centaur::deserialize(ValueMap& properties)
{
	Centaur* instance = new Centaur(properties);

	instance->autorelease();

	return instance;
}

Centaur::Centaur(ValueMap& properties) : super(properties,
	Centaur::MapKey,
	EntityResources::Enemies_EndianForest_Centaur_Animations,
	EntityResources::Enemies_EndianForest_Centaur_Emblem,
	Size(296.0f, 256.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Centaur::~Centaur()
{
}

Vec2 Centaur::getDialogueOffset()
{
	return Vec2(-48.0f, -212.0f);
}

LocalizedString* Centaur::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_EndianForest_Centaur::create();
}
