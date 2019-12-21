#include "FrostPortal.h"

#include "cocos/2d/CCDrawNode.h"
#include "cocos/2d/CCParticleSystemQuad.h"

#include "Resources/ParticleResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string FrostPortal::MapKeyFrostPortal = "frost-portal";

FrostPortal* FrostPortal::create(ValueMap& properties)
{
	FrostPortal* instance = new FrostPortal(properties);

	instance->autorelease();

	return instance;
}

FrostPortal::FrostPortal(ValueMap& properties) : super(properties, 96.0f, Color4B::RED)
{
	this->portalParticles = ParticleSystemQuad::create(ParticleResources::Portals_PortalFrost);
	this->edgeParticles = ParticleSystemQuad::create(ParticleResources::Portals_PortalEdge);

	this->portalEffectNode->addChild(this->edgeParticles);
	this->portalEffectNode->addChild(this->portalParticles);
}

FrostPortal::~FrostPortal()
{
}

void FrostPortal::onEnter()
{
	super::onEnter();
}

void FrostPortal::initializePositions()
{
	super::initializePositions();
}

void FrostPortal::initializeListeners()
{
	super::initializeListeners();
}

void FrostPortal::closePortal(bool instant)
{
	super::closePortal(instant);

	this->edgeParticles->stopSystem();
	this->portalParticles->stopSystem();
}

void FrostPortal::openPortal(bool instant)
{
	super::openPortal(instant);

	this->edgeParticles->start();
	this->portalParticles->start();
}
