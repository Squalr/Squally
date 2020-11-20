#include "WindGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Particles/SmartParticles.h"

#include "Resources/ParticleResources.h"

using namespace cocos2d;

WindGenericPreview* WindGenericPreview::create()
{
	WindGenericPreview* instance = new WindGenericPreview();

	instance->autorelease();

	return instance;
}

WindGenericPreview::WindGenericPreview()
{
	this->windParticles = SmartParticles::create(ParticleResources::Gust);

	this->windParticles->setAnchorPoint(Vec2::ZERO);
	this->windParticles->setPosVar(Vec2(HackablePreview::PreviewRadius, HackablePreview::PreviewRadius));
	this->windParticles->setGrouped();
	this->windParticles->setScale(0.4f);

	this->previewNode->addChild(this->windParticles);
}

WindGenericPreview::~WindGenericPreview()
{
}

HackablePreview* WindGenericPreview::clone()
{
	return WindGenericPreview::create();
}

void WindGenericPreview::onEnter()
{
	super::onEnter();
	
	this->windParticles->start();
}

void WindGenericPreview::initializePositions()
{
	super::initializePositions();

	const float offset = 192.0f;

	this->windParticles->setPosition(Vec2(0.0f, HackablePreview::PreviewRadius - offset));
}
