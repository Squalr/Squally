#include "Lazarus.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Lazarus::MapKey = "lazarus";

Lazarus* Lazarus::deserialize(ValueMap& properties)
{
	Lazarus* instance = new Lazarus(properties);

	instance->autorelease();

	return instance;
}

Lazarus::Lazarus(ValueMap& properties) : super(properties,
	Lazarus::MapKey,
	EntityResources::Enemies_LambdaCrypts_Lazarus_Animations,
	EntityResources::Enemies_LambdaCrypts_Lazarus_Emblem,
	Size(196.0f, 320.0f),
	0.9f,
	Vec2(0.0f, 0.0f))
{
}

Lazarus::~Lazarus()
{
}

Vec2 Lazarus::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Lazarus::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_LambdaCrypts_Lazarus::create();
}
