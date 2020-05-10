#include "EvilEye.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string EvilEye::MapKey = "evil-eye";

EvilEye* EvilEye::deserialize(ValueMap& properties)
{
	EvilEye* instance = new EvilEye(properties);

	instance->autorelease();

	return instance;
}

EvilEye::EvilEye(ValueMap& properties) : super(properties,
	EvilEye::MapKey,
	EntityResources::Enemies_VoidStar_EvilEye_Animations,
	EntityResources::Enemies_VoidStar_EvilEye_Emblem,
	Size(720.0f, 840.0f),
	0.6f,
	Vec2(0.0f, 0.0f))
{
}

EvilEye::~EvilEye()
{
}

Vec2 EvilEye::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* EvilEye::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_VoidStar_EvilEye::create();
}
