#include "WarpGateDM.h"

#include "Scenes/Platformer/Level/PreviewMap.h"

#include "Resources/MapResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string WarpGateDM::MapKey = "warp-gate-dm";

WarpGateDM* WarpGateDM::create(ValueMap& properties)
{
	WarpGateDM* instance = new WarpGateDM(properties);

	instance->autorelease();

	return instance;
}

WarpGateDM::WarpGateDM(ValueMap& properties) : super(properties)
{
}

WarpGateDM::~WarpGateDM()
{
}
