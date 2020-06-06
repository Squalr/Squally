#include "WarpGateUR.h"

#include "cocos/2d/CCDrawNode.h"

#include "Engine/Particles/SmartParticles.h"
#include "Scenes/Platformer/Level/PreviewMap.h"

#include "Resources/MapResources.h"
#include "Resources/ParticleResources.h"
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
	this->portalParticles = SmartParticles::create(ParticleResources::Portals_PortalWater, SmartParticles::CullInfo(Size(96.0f, 96.0f)));
	this->edgeParticles = SmartParticles::create(ParticleResources::Portals_PortalEdge, SmartParticles::CullInfo(Size(96.0f, 96.0f)));
	PreviewMap* map = PreviewMap::create(MapResources::WarpGatePreviewMaps_UnderflowRuins);
	
	this->edgeParticles->start();
	this->portalParticles->start();

	map->setPositionX(-map->getMapSize().width / 2.0f);
	map->setPositionY(-map->getMapSize().height / 2.0f);
	map->setPositionZ(-192.0f);

	this->contentNode->addChild(map);
	this->portalEffectNode->addChild(this->edgeParticles);
	this->portalEffectNode->addChild(this->portalParticles);
}

WarpGateUR::~WarpGateUR()
{
}

void WarpGateUR::onEnter()
{
	super::onEnter();
	
	this->edgeParticles->start();
	this->portalParticles->start();
}

void WarpGateUR::lock(bool animate)
{
	super::lock(animate);
	
	this->edgeParticles->stop();
	this->portalParticles->stop();
}

void WarpGateUR::unlock(bool animate)
{
	super::unlock(animate);
	
	this->edgeParticles->start();
	this->portalParticles->start();
}
