#include "KingZul.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string KingZul::MapKey = "king-zul";

KingZul* KingZul::deserialize(ValueMap& properties)
{
	KingZul* instance = new KingZul(properties);

	instance->autorelease();

	return instance;
}

KingZul::KingZul(ValueMap& properties) : super(properties,
	KingZul::MapKey,
	EntityResources::Enemies_LambdaCrypts_KingZul_Animations,
	EntityResources::Enemies_LambdaCrypts_KingZul_Emblem,
	Size(196.0f, 288.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

KingZul::~KingZul()
{
}

Vec2 KingZul::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* KingZul::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_LambdaCrypts_KingZul::create();
}
