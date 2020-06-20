#include "GoblinElf.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string GoblinElf::MapKey = "goblin-elf";

GoblinElf* GoblinElf::deserialize(ValueMap& properties)
{
	GoblinElf* instance = new GoblinElf(properties);

	instance->autorelease();

	return instance;
}

GoblinElf::GoblinElf(ValueMap& properties) : super(properties,
	GoblinElf::MapKey,
	EntityResources::Enemies_BallmerPeaks_GoblinElf_Animations,
	EntityResources::Enemies_BallmerPeaks_GoblinElf_Emblem,
	Size(140.0f, 296.0f),
	0.8f,
	Vec2(0.0f, 0.0f))
{
}

GoblinElf::~GoblinElf()
{
}

Vec2 GoblinElf::getDialogueOffset()
{
	return Vec2(-32.0f, -128.0f);
}

LocalizedString* GoblinElf::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_BallmerPeaks_GoblinElf::create();
}
