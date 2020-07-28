#include "LightningGolem.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string LightningGolem::MapKey = "lightning-golem";

LightningGolem* LightningGolem::deserialize(ValueMap& properties)
{
	LightningGolem* instance = new LightningGolem(properties);

	instance->autorelease();

	return instance;
}

LightningGolem::LightningGolem(ValueMap& properties) : super(properties,
	LightningGolem::MapKey,
	EntityResources::Enemies_VoidStar_LightningGolem_Animations,
	EntityResources::Enemies_VoidStar_LightningGolem_Emblem,
	Size(768.0f, 840.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

LightningGolem::~LightningGolem()
{
}

Vec2 LightningGolem::getDialogueOffset()
{
	return Vec2(-32.0f, -380.0f);
}

LocalizedString* LightningGolem::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_VoidStar_LightningGolem::create();
}
