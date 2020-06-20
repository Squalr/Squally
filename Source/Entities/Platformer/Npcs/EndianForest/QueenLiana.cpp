#include "QueenLiana.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string QueenLiana::MapKey = "queen-liana";

QueenLiana* QueenLiana::deserialize(ValueMap& properties)
{
	QueenLiana* instance = new QueenLiana(properties);

	instance->autorelease();

	return instance;
}

QueenLiana::QueenLiana(ValueMap& properties) : super(properties,
	QueenLiana::MapKey,
	EntityResources::Npcs_EndianForest_QueenLiana_Animations,
	EntityResources::Npcs_EndianForest_QueenLiana_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

QueenLiana::~QueenLiana()
{
}

Vec2 QueenLiana::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* QueenLiana::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_EndianForest_QueenLiana::create();
}
