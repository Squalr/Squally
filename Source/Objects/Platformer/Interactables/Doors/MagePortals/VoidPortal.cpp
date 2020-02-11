#include "VoidPortal.h"

#include "cocos/2d/CCDrawNode.h"

#include "Engine/Particles/SmartParticles.h"

#include "Resources/ParticleResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string VoidPortal::MapKeyVoidPortal = "void-portal";

VoidPortal* VoidPortal::create(ValueMap& properties)
{
	VoidPortal* instance = new VoidPortal(properties);

	instance->autorelease();

	return instance;
}

VoidPortal::VoidPortal(ValueMap& properties) : super(properties, 96.0f, Color4B::BLACK)
{
	this->portalParticles = SmartParticles::create(ParticleResources::Portals_PortalVoid, SmartParticles::CullInfo(Size(96.0f, 96.0f)));

	this->portalEffectNode->addChild(this->portalParticles);
}

VoidPortal::~VoidPortal()
{
}

void VoidPortal::onEnter()
{
	super::onEnter();
}

void VoidPortal::initializePositions()
{
	super::initializePositions();
}

void VoidPortal::initializeListeners()
{
	super::initializeListeners();
}

void VoidPortal::closePortal(bool instant)
{
	super::closePortal(instant);

	this->edgeParticles->stop();
	this->portalParticles->stop();
}

void VoidPortal::openPortal(bool instant)
{
	super::openPortal(instant);

	this->edgeParticles->start();
	this->portalParticles->start();
}
