#include "WarpGateUR.h"

#include "Scenes/Platformer/Level/PreviewMap.h"

#include "Resources/MapResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string WarpGateUR::MapKey = "warp-gate-ur";

WarpGateUR* WarpGateUR::create(ValueMap& properties)
{
	WarpGateUR* instance = new WarpGateUR(properties);

	instance->autorelease();

	return instance;
}

WarpGateUR::WarpGateUR(ValueMap& properties) : super(properties)
{
	PreviewMap* map = PreviewMap::create(MapResources::WarpGatePreviewMaps_UnderflowRuins);

	map->setPositionX(-map->getMapSize().width / 2.0f);
	map->setPositionY(-map->getMapSize().height / 2.0f);
	map->setPositionZ(-256.0f);

	this->contentNode->addChild(map);
}

WarpGateUR::~WarpGateUR()
{
}
