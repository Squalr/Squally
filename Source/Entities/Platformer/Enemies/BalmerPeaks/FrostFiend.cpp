#include "FrostFiend.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string FrostFiend::MapKey = "frost-fiend";

FrostFiend* FrostFiend::deserialize(ValueMap& properties)
{
	FrostFiend* instance = new FrostFiend(properties);

	instance->autorelease();

	return instance;
}

FrostFiend::FrostFiend(ValueMap& properties) : super(properties,
	FrostFiend::MapKey,
	EntityResources::Enemies_BalmerPeaks_FrostFiend_Animations,
	EntityResources::Enemies_BalmerPeaks_FrostFiend_Emblem,
	Size(212.0f, 296.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

FrostFiend::~FrostFiend()
{
}

Vec2 FrostFiend::getDialogueOffset()
{
	return Vec2(-32.0f, -128.0f);
}

LocalizedString* FrostFiend::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_BalmerPeaks_FrostFiend::create();
}
