#include "NaturePortal.h"

#include "cocos/2d/CCDrawNode.h"
#include "cocos/2d/CCParticleSystemQuad.h"

#include "Resources/ParticleResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string NaturePortal::MapKeyNaturePortal = "nature-portal";

NaturePortal* NaturePortal::create(ValueMap& properties)
{
	NaturePortal* instance = new NaturePortal(properties);

	instance->autorelease();

	return instance;
}

NaturePortal::NaturePortal(ValueMap& properties) : super(properties, 96.0f, Color4B(14, 82, 24, 255))
{
	this->portalParticles = ParticleSystemQuad::create(ParticleResources::Portals_PortalNature);
	this->edgeParticles = ParticleSystemQuad::create(ParticleResources::Portals_PortalNatureEdge);

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
