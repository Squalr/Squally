#include "BlizzardGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Particles/SmartParticles.h"

#include "Resources/ParticleResources.h"

using namespace cocos2d;

BlizzardGenericPreview* BlizzardGenericPreview::create()
{
	BlizzardGenericPreview* instance = new BlizzardGenericPreview();

	instance->autorelease();

	return instance;
}

BlizzardGenericPreview::BlizzardGenericPreview()
{
	this->blizzardParticles = SmartParticles::create(ParticleResources::Gust);

	this->blizzardParticles->setAnchorPoint(Vec2::ZERO);
	this->blizzardParticles->setPosVar(Vec2(HackablePreview::PreviewRadius, HackablePreview::PreviewRadius));
	this->blizzardParticles->setGrouped();
	this->blizzardParticles->setScale(0.4f);

	this->previewNode->addChild(this->blizzardParticles);
}

BlizzardGenericPreview::~BlizzardGenericPreview()
{
}

HackablePreview* BlizzardGenericPreview::clone()
{
	return BlizzardGenericPreview::create();
}

void BlizzardGenericPreview::onEnter()
{
	super::onEnter();
	
	this->blizzardParticles->start();
}

void BlizzardGenericPreview::initializePositions()
{
	super::initializePositions();

	const float offset = 192.0f;

	this->blizzardParticles->setPosition(Vec2(0.0f, HackablePreview::PreviewRadius - offset));
}
