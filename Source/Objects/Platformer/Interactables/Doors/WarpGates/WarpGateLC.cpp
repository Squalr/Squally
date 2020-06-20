#include "WarpGateLC.h"

#include "Scenes/Platformer/Level/PreviewMap.h"

#include "Resources/MapResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string WarpGateLC::MapKey = "warp-gate-lc";

WarpGateLC* WarpGateLC::create(ValueMap& properties)
{
	WarpGateLC* instance = new WarpGateLC(properties);

	instance->autorelease();

	return instance;
}

WarpGateLC::WarpGateLC(ValueMap& properties) : super(properties)
{
}

WarpGateLC::~WarpGateLC()
{
}
