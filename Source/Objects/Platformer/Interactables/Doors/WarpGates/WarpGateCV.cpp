#include "WarpGateCV.h"

#include "Scenes/Platformer/Level/PreviewMap.h"

#include "Resources/MapResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string WarpGateCV::MapKey = "warp-gate-cv";

WarpGateCV* WarpGateCV::create(ValueMap& properties)
{
	WarpGateCV* instance = new WarpGateCV(properties);

	instance->autorelease();

	return instance;
}

WarpGateCV::WarpGateCV(ValueMap& properties) : super(properties)
{
}

WarpGateCV::~WarpGateCV()
{
}
