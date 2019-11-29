#include "VoidPortal.h"

#include "cocos/2d/CCDrawNode.h"
#include "cocos/2d/CCParticleSystemQuad.h"

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
	this->portalParticles = ParticleSystemQuad::create(ParticleResources::Portals_PortalVoid);

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
