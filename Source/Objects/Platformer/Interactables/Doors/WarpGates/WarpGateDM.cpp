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
	PreviewMap* map = PreviewMap::create(MapResources::WarpGatePreviewMaps_DataMines);

	map->setPositionX(-map->getMapSize().width / 2.0f);
	map->setPositionY(-map->getMapSize().height / 2.0f);
	map->setPositionZ(-320.0f);

	this->mapNode->addChild(map);
}

WarpGateDM::~WarpGateDM()
{
}
