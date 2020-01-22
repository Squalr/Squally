#include "ParticleObject.h"

#include "cocos/2d/CCDrawNode.h"
#include "cocos/2d/CCParticleSystemQuad.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Camera/GameCamera.h"
#include "Engine/Utils/GameUtils.h"

using namespace cocos2d;

ParticleObject* ParticleObject::create(std::string particleResource, Size size)
{
	ParticleObject* instance = new ParticleObject(particleResource, size);

	instance->autorelease();

	return instance;
}

ParticleObject::ParticleObject(std::string particleResource, Size size) : super()
{
	this->particles = ParticleSystemQuad::create(particleResource);
	this->debugDrawNode = DrawNode::create();
	this->boundsRect = Rect(Vec2::ZERO, size);

	this->particles->setUpdateWhileNotVisibleDisabled(true);

	this->debugDrawNode->drawSolidRect(-Vec2(size) / 2.0f, Vec2(size) / 2.0f, Color4F::GREEN);

	this->addChild(this->debugDrawNode);
	this->addChild(this->particles);
}

ParticleObject::~ParticleObject()
{ 
}

void ParticleObject::onEnter()
{
	super::onEnter();
	
	this->optimizationHideOffscreenParticles();
	this->scheduleUpdate();
}

void ParticleObject::onDeveloperModeEnable(int debugLevel)
{
	if (debugLevel >= 2)
	{
		this->debugDrawNode->setVisible(true);
	}
}

void ParticleObject::onDeveloperModeDisable()
{
	this->debugDrawNode->setVisible(false);
}

void ParticleObject::update(float dt)
{
	super::update(dt);
	
	this->optimizationHideOffscreenParticles();
}

ParticleSystem* ParticleObject::getParticles()
{
	return this->particles;
}

void ParticleObject::optimizationHideOffscreenParticles()
{
	float zoom = GameCamera::getInstance()->getCameraZoomOnTarget(this);
	static const Size Padding = Size(384.0f, 384.0f);
	Size clipSize = (Director::getInstance()->getVisibleSize() + Padding) * zoom;
	Rect cameraRect = Rect(GameCamera::getInstance()->getCameraPosition() - Vec2(clipSize.width / 2.0f, clipSize.height / 2.0f), clipSize);
	Rect thisRect = this->boundsRect;

	thisRect.origin += GameUtils::getWorldCoords(this);

	if (cameraRect.intersectsRect(thisRect))
	{
		this->particles->setVisible(true);
	}
	else
	{
		this->particles->setVisible(false);
	}
}
