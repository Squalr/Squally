#include "Matu.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Matu::MapKey = "matu";

Matu* Matu::deserialize(ValueMap& properties)
{
	Matu* instance = new Matu(properties);

	instance->autorelease();

	return instance;
}

Matu::Matu(ValueMap& properties) : super(properties,
	Matu::MapKey,
	EntityResources::Npcs_EndianForest_Matu_Animations,
	EntityResources::Npcs_EndianForest_Matu_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Matu::~Matu()
{
}

Vec2 Matu::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Matu::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_EndianForest_Matu::create();
}
