#include "FirePortal.h"

#include "cocos/2d/CCParticleSystemQuad.h"

#include "Resources/ParticleResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string FirePortal::MapKeyFirePortal = "fire-portal";

FirePortal* FirePortal::create(ValueMap& properties)
{
	FirePortal* instance = new FirePortal(properties);

	instance->autorelease();

	return instance;
}

FirePortal::FirePortal(ValueMap& properties) : super(properties)
{
	this->portalParticles = ParticleSystemQuad::create(ParticleResources::Portals_PortalFire);
	this->edgeParticles = ParticleSystemQuad::create(ParticleResources::Portals_PortalEdge);

	this->contentNode->addChild(this->portalParticles);
	this->contentNode->addChild(this->edgeParticles);
}

FirePortal::~FirePortal()
{
}

void FirePortal::onEnter()
{
	super::onEnter();
}

void FirePortal::initializePositions()
{
	super::initializePositions();
}

void FirePortal::initializeListeners()
{
	super::initializeListeners();
}
