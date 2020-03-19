#include "Gorgon.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Gorgon::MapKey = "gorgon";

Gorgon* Gorgon::deserialize(ValueMap& properties)
{
	Gorgon* instance = new Gorgon(properties);

	instance->autorelease();

	return instance;
}

Gorgon::Gorgon(ValueMap& properties) : super(properties,
	Gorgon::MapKey,
	EntityResources::Enemies_EndianForest_Gorgon_Animations,
	EntityResources::Enemies_EndianForest_Gorgon_Emblem,
	Size(512.0f, 512.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Gorgon::~Gorgon()
{
}

Vec2 Gorgon::getDialogueOffset()
{
	return Vec2(-32.0f, -280.0f);
}

LocalizedString* Gorgon::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_EndianForest_Gorgon::create();
}
