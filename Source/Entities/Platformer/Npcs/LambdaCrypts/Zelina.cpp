#include "Zelina.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Zelina::MapKey = "zelina";

Zelina* Zelina::deserialize(ValueMap& properties)
{
	Zelina* instance = new Zelina(properties);

	instance->autorelease();

	return instance;
}

Zelina::Zelina(ValueMap& properties) : super(properties,
	Zelina::MapKey,
	EntityResources::Npcs_LambdaCrypts_Zelina_Animations,
	EntityResources::Npcs_LambdaCrypts_Zelina_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Zelina::~Zelina()
{
}

Vec2 Zelina::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Zelina::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_LambdaCrypts_Zelina::create();
}
