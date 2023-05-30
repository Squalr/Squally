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
	EntityResources::Enemies__Deprecated_Centaur_Animations,
	EntityResources::Enemies__Deprecated_Centaur_Emblem,
	CSize(296.0f, 256.0f),
	1.0f)
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
