#include "TriangleFadeHud.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCDrawNode.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

using namespace cocos2d;

TriangleFadeHud* TriangleFadeHud::create()
{
	TriangleFadeHud* instance = new TriangleFadeHud();

	instance->autorelease();

	return instance;
}

TriangleFadeHud::TriangleFadeHud()
{
	this->upperTraingle = DrawNode::create();
	this->leftTriangle = DrawNode::create();
	this->rightTriangle = DrawNode::create();
	this->bottomTriangle = DrawNode::create();

	this->buildShapes();

	this->addChild(this->upperTraingle);
	this->addChild(this->leftTriangle);
	this->addChild(this->rightTriangle);
	this->addChild(this->bottomTriangle);
}

TriangleFadeHud::~TriangleFadeHud()
{
}

void TriangleFadeHud::initializePositions()
{
	super::initializePositions();

	this->resetAnim();
}

void TriangleFadeHud::runAnim()
{
	const float duration = 0.5f;

	this->upperTraingle->runAction(MoveTo::create(duration, Vec2::ZERO));
	this->leftTriangle->runAction(MoveTo::create(duration, Vec2::ZERO));
	this->rightTriangle->runAction(MoveTo::create(duration, Vec2::ZERO));
	this->bottomTriangle->runAction(MoveTo::create(duration, Vec2::ZERO));

	this->runAction(Sequence::create(
		DelayTime::create(duration),
		CallFunc::create([=]()
		{
			this->fillSeams();
		}),
		nullptr
	));
}

void TriangleFadeHud::resetAnim()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->upperTraingle->setPosition(Vec2(0.0f, visibleSize.height / 2.0f));
	this->leftTriangle->setPosition(Vec2(-visibleSize.width / 2.0f, 0.0f));
	this->rightTriangle->setPosition(Vec2(visibleSize.width / 2.0f, 0.0f));
	this->bottomTriangle->setPosition(Vec2(0.0f, -visibleSize.height / 2.0f));
}

void TriangleFadeHud::buildShapes()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	Vec2 center = Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f);
	Vec2 topLeft = Vec2(0.0f, visibleSize.height);
	Vec2 topRight = Vec2(visibleSize.width, visibleSize.height);
	Vec2 bottomLeft = Vec2(0.0f, 0.0f);
	Vec2 bottomRight = Vec2(visibleSize.width, 0.0f);

	std::vector<Vec2> triangleA = { topLeft, center, topRight };
	std::vector<Vec2> triangleB = { topLeft, center, bottomLeft };
	std::vector<Vec2> triangleC = { bottomLeft, center, bottomRight };
	std::vector<Vec2> triangleD = { bottomRight, center, topRight };

	this->upperTraingle->drawSolidPoly(triangleA.data(), triangleA.size(), Color4F::BLACK);
	this->leftTriangle->drawSolidPoly(triangleB.data(), triangleB.size(), Color4F::BLACK);
	this->bottomTriangle->drawSolidPoly(triangleC.data(), triangleC.size(), Color4F::BLACK);
	this->rightTriangle->drawSolidPoly(triangleD.data(), triangleD.size(), Color4F::BLACK);
}
