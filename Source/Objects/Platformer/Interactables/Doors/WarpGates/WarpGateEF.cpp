#include "WarpGateEF.h"

#include "Scenes/Platformer/Level/PreviewMap.h"

#include "Resources/MapResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string WarpGateEF::MapKey = "warp-gate-ef";

WarpGateEF* WarpGateEF::create(ValueMap& properties)
{
	WarpGateEF* instance = new WarpGateEF(properties);

	instance->autorelease();

	return instance;
}

WarpGateEF::WarpGateEF(ValueMap& properties) : super(properties)
{
	PreviewMap* map = PreviewMap::create(MapResources::WarpGatePreviewMaps_EndianForest);

	map->setPositionX(-map->getMapSize().width / 2.0f);
	map->setPositionY(-map->getMapSize().height / 2.0f);
	map->setPositionZ(-320.0f);

	this->mapNode->addChild(map);
}

WarpGateEF::~WarpGateEF()
{
}
