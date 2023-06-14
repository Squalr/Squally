#include "TvFadeHud.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCDrawNode.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

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

	this->buildShapes();

	this->addChild(this->upperRectangle);
	this->addChild(this->bottomRectangle);
}

TvFadeHud::~TvFadeHud()
{
}

void TvFadeHud::initializePositions()
{
	super::initializePositions();

	this->resetAnim();
}

void TvFadeHud::runAnim()
{
	const float duration = 0.5f;

	this->upperRectangle->runAction(MoveTo::create(duration, Vec2::ZERO));
	this->bottomRectangle->runAction(MoveTo::create(duration, Vec2::ZERO));

	this->runAction(Sequence::create(
		DelayTime::create(duration),
		CallFunc::create([=]()
		{
			this->fillSeams();
		}),
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
