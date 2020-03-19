#include "FrostPortal.h"

#include "cocos/2d/CCDrawNode.h"

#include "Engine/Particles/SmartParticles.h"

#include "Resources/ParticleResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string FrostPortal::MapKey = "frost-portal";

FrostPortal* FrostPortal::create(ValueMap& properties)
{
	FrostPortal* instance = new FrostPortal(properties);

	instance->autorelease();

	return instance;
}

FrostPortal::FrostPortal(ValueMap& properties) : super(properties, 96.0f, Color4B::BLUE)
{
	this->portalParticles = SmartParticles::create(ParticleResources::Portals_PortalFrost, SmartParticles::CullInfo(Size(96.0f, 96.0f)));
	this->edgeParticles = SmartParticles::create(ParticleResources::Portals_PortalEdge, SmartParticles::CullInfo(Size(96.0f, 96.0f)));

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

	this->edgeParticles->stop();
	this->portalParticles->stop();
}

void FrostPortal::openPortal(bool instant)
{
	super::openPortal(instant);

	this->edgeParticles->start();
	this->portalParticles->start();
}
