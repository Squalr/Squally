#include "WarpGateFF.h"

#include "Scenes/Platformer/Level/PreviewMap.h"

#include "Resources/MapResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string WarpGateFF::MapKey = "warp-gate-ff";

WarpGateFF* WarpGateFF::create(ValueMap& properties)
{
	WarpGateFF* instance = new WarpGateFF(properties);

	instance->autorelease();

	return instance;
}

WarpGateFF::WarpGateFF(ValueMap& properties) : super(properties)
{
	PreviewMap* map = PreviewMap::create(MapResources::WarpGatePreviewMaps_FirewallFissure);

	map->setPositionX(-map->getMapSize().width / 2.0f);
	map->setPositionY(-map->getMapSize().height / 2.0f);
	map->setPositionZ(-320.0f);

	this->mapNode->addChild(map);
}

WarpGateFF::~WarpGateFF()
{
}
