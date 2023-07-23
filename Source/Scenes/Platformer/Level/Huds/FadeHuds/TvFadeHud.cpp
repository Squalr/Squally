#include "TvFadeHud.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCDrawNode.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

TvFadeHud* TvFadeHud::create()
{
	TvFadeHud* instance = new TvFadeHud();

	instance->autorelease();

	return instance;
}

TvFadeHud::TvFadeHud()
{
	this->upperRectangle = DrawNode::create();
	this->bottomRectangle = DrawNode::create();
	this->glowSmall = Sprite::create(FXResources::TvGlows_GlowSmall);
	this->glowLarge = Sprite::create(FXResources::TvGlows_GlowLarge);

	this->buildShapes();

	this->glowSmall->setOpacity(0);
	this->glowLarge->setOpacity(0);

	this->addChild(this->upperRectangle);
	this->addChild(this->bottomRectangle);
	this->addChild(this->glowSmall);
	this->addChild(this->glowLarge);
}

TvFadeHud::~TvFadeHud()
{
}

void TvFadeHud::initializePositions()
{
	super::initializePositions();

	CSize visibleSize = Director::getInstance()->getVisibleSize();

	this->glowSmall->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->glowLarge->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));

	this->resetAnim();
}

void TvFadeHud::runAnim()
{
	const float BlackDuration = 0.5f;

	this->glowSmall->setOpacity(0);
	this->glowLarge->setOpacity(0);

	this->upperRectangle->runAction(EaseSineIn::create(MoveTo::create(BlackDuration, Vec2::ZERO)));
	this->bottomRectangle->runAction(EaseSineIn::create(MoveTo::create(BlackDuration, Vec2::ZERO)));

	this->runAction(Sequence::create(
		DelayTime::create(BlackDuration),
		CallFunc::create([=]()
		{
			this->fillSeams();
		}),
		nullptr
	));

	const float GlowLargeOnsetDuration = 0.35f;
	const float GlowLargeSustainDuration = 0.35f;
	const float GlowLargeReleaseDuration = 0.15f;

	this->glowLarge->runAction(Sequence::create(
		DelayTime::create(GlowLargeOnsetDuration),
		FadeTo::create(GlowLargeSustainDuration, 255),
		FadeTo::create(GlowLargeReleaseDuration, 0),
		nullptr
	));

	const float GlowSmallOnsetDuration = 0.5f;
	const float GlowSmallSustainDuration = 0.25f;
	const float GlowSmallReleaseDuration = 0.15f;

	this->glowSmall->runAction(Sequence::create(
		DelayTime::create(GlowSmallOnsetDuration),
		FadeTo::create(GlowSmallSustainDuration, 255),
		FadeTo::create(GlowSmallReleaseDuration, 0),
		nullptr
	));
}

void TvFadeHud::resetAnim()
{
	CSize visibleSize = Director::getInstance()->getVisibleSize();

	this->upperRectangle->setPosition(Vec2(0.0f, visibleSize.height / 2.0f));
	this->bottomRectangle->setPosition(Vec2(0.0f, -visibleSize.height / 2.0f));
}

void TvFadeHud::buildShapes()
{
	CSize visibleSize = Director::getInstance()->getVisibleSize();

	Vec2 centerLeft = Vec2(0.0f, visibleSize.height / 2.0f);
	Vec2 centerRight = Vec2(visibleSize.width, visibleSize.height / 2.0f);
	Vec2 topLeft = Vec2(0.0f, visibleSize.height);
	Vec2 topRight = Vec2(visibleSize.width, visibleSize.height);
	Vec2 bottomLeft = Vec2(0.0f, 0.0f);
	Vec2 bottomRight = Vec2(visibleSize.width, 0.0f);

	std::vector<Vec2> shapeA = { topLeft, centerLeft, centerRight, topRight };
	std::vector<Vec2> shapeB = { bottomLeft, centerLeft, centerRight, bottomRight };

	this->upperRectangle->drawSolidPoly(shapeA.data(), shapeA.size(), Color4F::BLACK);
	this->bottomRectangle->drawSolidPoly(shapeB.data(), shapeB.size(), Color4F::BLACK);
}
