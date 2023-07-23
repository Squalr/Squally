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
	PreviewMap* map = PreviewMap::create(MapResources::WarpGatePreviewMaps_BallmerPeaks);

	map->setPositionX(-map->getMapSize().width / 2.0f);
	map->setPositionY(-map->getMapSize().height / 2.0f);
	map->setPositionZ(-320.0f);

	this->mapNode->addChild(map);
}

WarpGateBP::~WarpGateBP()
{
}
