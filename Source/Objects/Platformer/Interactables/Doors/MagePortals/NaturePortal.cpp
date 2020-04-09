#include "NaturePortal.h"

#include "cocos/2d/CCDrawNode.h"

#include "Engine/Particles/SmartParticles.h"

#include "Resources/ParticleResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string NaturePortal::MapKey = "nature-portal";

NaturePortal* NaturePortal::create(ValueMap& properties)
{
	NaturePortal* instance = new NaturePortal(properties);

	instance->autorelease();

	return instance;
}

NaturePortal::NaturePortal(ValueMap& properties) : super(properties, 96.0f, Color4B(14, 82, 24, 255))
{
	this->portalParticles = SmartParticles::create(ParticleResources::Portals_PortalNature, SmartParticles::CullInfo(Size(96.0f, 96.0f)));
	this->edgeParticles = SmartParticles::create(ParticleResources::Portals_PortalNatureEdge, SmartParticles::CullInfo(Size(96.0f, 96.0f)));
	
	this->edgeParticles->start();
	this->portalParticles->start();

	this->portalEffectNode->addChild(this->edgeParticles);
	this->portalEffectNode->addChild(this->portalParticles);
}

NaturePortal::~NaturePortal()
{
}

void NaturePortal::onEnter()
{
	super::onEnter();
}

void NaturePortal::initializePositions()
{
	super::initializePositions();
}

void NaturePortal::initializeListeners()
{
	super::initializeListeners();
}

void NaturePortal::closePortal(bool instant)
{
	super::closePortal(instant);

	this->edgeParticles->stop();
	this->portalParticles->stop();
}

void NaturePortal::openPortal(bool instant)
{
	super::openPortal(instant);

	this->edgeParticles->start();
	this->portalParticles->start();
}
