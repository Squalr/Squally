#include "Garrick.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Garrick::MapKey = "garrick";

Garrick* Garrick::deserialize(ValueMap& properties)
{
	Garrick* instance = new Garrick(properties);

	instance->autorelease();

	return instance;
}

Garrick::Garrick(ValueMap& properties) : super(properties,
	Garrick::MapKey,
	EntityResources::Npcs_LambdaCrypts_Garrick_Animations,
	EntityResources::Npcs_LambdaCrypts_Garrick_Emblem,
	Size(112.0f, 160.0f),
	0.9f,
	Vec2(0.0f, 0.0f))
{
}

Garrick::~Garrick()
{
}

Vec2 Garrick::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Garrick::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_LambdaCrypts_Garrick::create();
}
