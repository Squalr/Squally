#include "WarpGate.h"

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

const std::string WarpGate::TagWarpGate = "warp-gate";

WarpGate::WarpGate(ValueMap& properties) : super(properties, Size(128.0f, 256.0f))
{
	this->mapNodeContainer = Node::create();
	this->mapNode = Node::create();
	this->particlesNode = Node::create();
	this->mapClip = SmartClippingNode::create(this->mapNodeContainer, Size(256.0f, 488.0f));
	this->doorClosed = Sprite::create(ObjectResources::Doors_WarpGate_WarpGateClosed);
	this->doorFrame = Sprite::create(ObjectResources::Doors_WarpGate_WarpGateFrame);
	this->portalOpenSound = WorldSound::create(SoundResources::Platformer_Objects_Doors_Portals_Portal);
	this->centerParticles = SmartParticles::create(ParticleResources::WarpGates_PortalCenter, SmartParticles::CullInfo(Size(256.0f, 512.0f)));
	this->edgeParticlesLeft = SmartParticles::create(ParticleResources::WarpGates_PortalEdgeVertical, SmartParticles::CullInfo(Size(64.0f, 512.0f)));
	this->edgeParticlesRight = SmartParticles::create(ParticleResources::WarpGates_PortalEdgeVertical, SmartParticles::CullInfo(Size(64.0f, 512.0f)));
	this->edgeParticlesUp = SmartParticles::create(ParticleResources::WarpGates_PortalEdgeHorizontal, SmartParticles::CullInfo(Size(256.0f, 64.0f)));
	this->edgeParticlesDown = SmartParticles::create(ParticleResources::WarpGates_PortalEdgeHorizontal, SmartParticles::CullInfo(Size(256.0f, 64.0f)));
	
	this->addTag(WarpGate::TagWarpGate);

	this->mapNodeContainer->addChild(this->mapNode);
	this->mapNodeContainer->addChild(this->particlesNode);
	this->particlesNode->addChild(this->centerParticles);
	this->particlesNode->addChild(this->edgeParticlesLeft);
	this->particlesNode->addChild(this->edgeParticlesRight);
	this->particlesNode->addChild(this->edgeParticlesUp);
	this->particlesNode->addChild(this->edgeParticlesDown);
	this->contentNode->addChild(this->mapClip);
	this->contentNode->addChild(this->doorFrame);
	this->contentNode->addChild(this->doorClosed);
	this->addChild(this->portalOpenSound);
}

WarpGate::~WarpGate()
{
}

void WarpGate::onEnter()
{
	super::onEnter();

	this->centerParticles->start();
	this->edgeParticlesLeft->start();
	this->edgeParticlesRight->start();
	this->edgeParticlesUp->start();
	this->edgeParticlesDown->start();
}

void WarpGate::initializePositions()
{
	super::initializePositions();

	const float YOffset = -88.0f;

	this->mapClip->setPosition(Vec2(0.0f, YOffset));
	this->centerParticles->setPosition(Vec2(0.0f, 0.0f));
	this->edgeParticlesLeft->setPosition(Vec2(-128.0f + 32.0f, 0.0f));
	this->edgeParticlesRight->setPosition(Vec2(128.0f - 32.0f, 0.0f));
	this->edgeParticlesUp->setPosition(Vec2(0.0f,  204.0f - 32.0f));
	this->edgeParticlesDown->setPosition(Vec2(0.0f, -204.0f - 32.0f));
}

void WarpGate::initializeListeners()
{
	super::initializeListeners();
}

void WarpGate::lock(bool animate)
{
	super::lock(animate);

	this->doorFrame->setVisible(false);
	this->doorClosed->setVisible(true);
	this->mapNodeContainer->setVisible(false);

	this->centerParticles->stop();
	this->edgeParticlesLeft->stop();
	this->edgeParticlesRight->stop();
	this->edgeParticlesUp->stop();
	this->edgeParticlesDown->stop();
}

void WarpGate::unlock(bool animate)
{
	super::unlock(animate);

	this->doorFrame->setVisible(true);
	this->doorClosed->setVisible(false);
	this->mapNodeContainer->setVisible(true);
	
	this->centerParticles->start();
	this->edgeParticlesLeft->start();
	this->edgeParticlesRight->start();
	this->edgeParticlesUp->start();
	this->edgeParticlesDown->start();
}
