#include "WarpGateVS.h"

#include "Scenes/Platformer/Level/PreviewMap.h"

#include "Resources/MapResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string WarpGateVS::MapKey = "warp-gate-vs";

WarpGateVS* WarpGateVS::create(ValueMap& properties)
{
	WarpGateVS* instance = new WarpGateVS(properties);

	instance->autorelease();

	return instance;
}

WarpGateVS::WarpGateVS(ValueMap& properties) : super(properties)
{
	PreviewMap* map = PreviewMap::create(MapResources::WarpGatePreviewMaps_EndianForest);

	map->setPositionX(-map->getMapSize().width / 2.0f);
	map->setPositionY(-map->getMapSize().height / 2.0f);
	map->setPositionZ(-320.0f);

	this->mapNode->addChild(map);
}

WarpGateVS::~WarpGateVS()
{
}
