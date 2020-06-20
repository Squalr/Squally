#include "WarpGateBP.h"

#include "Scenes/Platformer/Level/PreviewMap.h"

#include "Resources/MapResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string WarpGateBP::MapKey = "warp-gate-bp";

WarpGateBP* WarpGateBP::create(ValueMap& properties)
{
	WarpGateBP* instance = new WarpGateBP(properties);

	instance->autorelease();

	return instance;
}

WarpGateBP::WarpGateBP(ValueMap& properties) : super(properties)
{
}

WarpGateBP::~WarpGateBP()
{
}
