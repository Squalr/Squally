#include "HellGate.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Particles/SmartParticles.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/UI/SmartClippingNode.h"

#include "Resources/ObjectResources.h"
#include "Resources/ParticleResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string HellGate::MapKey = "hell-gate";

HellGate* HellGate::create(ValueMap& properties)
{
	HellGate* instance = new HellGate(properties);

	instance->autorelease();

	return instance;
}

HellGate::HellGate(ValueMap& properties) : super(properties, CSize(424.0f, 424.0f))
{
	this->mapNodeContainer = Node::create();
	this->mapNode = Node::create();
	this->particlesNode = Node::create();
	this->clipping = SmartClippingNode::create(this->mapNodeContainer, 212.0f);
	this->doorFrame = Sprite::create(ObjectResources::Doors_HellGate_HellGateFrame);
	this->portalOpenSound = WorldSound::create(SoundResources::Platformer_Objects_Doors_Portals_Portal);
	this->fireParticles = SmartParticles::create(ParticleResources::Portals_HellPortal, SmartParticles::CullInfo(CSize(424.0f, 424.0f)));
	this->centerParticles = SmartParticles::create(ParticleResources::WarpGates_PortalCenter, SmartParticles::CullInfo(CSize(424.0f, 424.0f)));

	this->clipping->enableAllowDebugDraw();
	
	this->mapNodeContainer->addChild(this->mapNode);
	this->mapNodeContainer->addChild(this->particlesNode);
	this->particlesNode->addChild(this->fireParticles);
	this->particlesNode->addChild(this->centerParticles);
	this->contentNode->addChild(this->clipping);
	this->contentNode->addChild(this->doorFrame);
	this->addChild(this->portalOpenSound);
}

HellGate::~HellGate()
{
}

void HellGate::onEnter()
{
	super::onEnter();

	this->fireParticles->start();
	this->centerParticles->start();
}

void HellGate::initializePositions()
{
	super::initializePositions();

	this->clipping->setPosition(Vec2(-8.0f, -64.0f));
}

void HellGate::initializeListeners()
{
	super::initializeListeners();
}

void HellGate::lock(bool animate)
{
	super::lock(animate);

	this->mapNodeContainer->setVisible(false);

	this->fireParticles->stop();
	this->centerParticles->stop();
}

void HellGate::unlock(bool animate)
{
	super::unlock(animate);

	this->mapNodeContainer->setVisible(true);
	
	this->fireParticles->start();
	this->centerParticles->start();
}
