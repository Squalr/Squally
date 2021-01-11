#include "FadeHud.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCDrawNode.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Optimization/LazyNode.h"
#include "Scenes/Platformer/Level/Huds/FadeHuds/NormalFadeHud.h"
#include "Scenes/Platformer/Level/Huds/FadeHuds/TriangleFadeHud.h"

using namespace cocos2d;

const float FadeHud::AnimationTimeBudget = 0.75f;

FadeHud* FadeHud::create()
{
	FadeHud* instance = new FadeHud();

	instance->autorelease();

	return instance;
}

FadeHud::FadeHud()
{
	this->normalFadeHud = LazyNode<NormalFadeHud>::create([](){ return NormalFadeHud::create(); });
	this->triangleFadeHud = LazyNode<TriangleFadeHud>::create([](){ return TriangleFadeHud::create(); });
	this->resetScreen = DrawNode::create();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	this->resetScreen->drawSolidRect(Vec2::ZERO, Vec2(visibleSize), Color4F::BLACK);
	this->resetScreen->setOpacity(0);

	this->addChild(this->resetScreen);
	this->addChild(this->normalFadeHud);
	this->addChild(this->triangleFadeHud);
}

FadeHud::~FadeHud()
{
}

void FadeHud::runAnim(FadeHudType fadeHudType)
{
	switch(fadeHudType)
	{
		case FadeHudType::Normal:
		{
			this->normalFadeHud->lazyGet()->runAnim();
			break;
		}
		case FadeHudType::Triangles:
		{
			this->triangleFadeHud->lazyGet()->runAnim();
			break;
		}
	}
}

void FadeHud::resetAnims()
{
	if (this->normalFadeHud->isBuilt())
	{
		this->normalFadeHud->lazyGet()->resetAnim();
	}

	if (this->triangleFadeHud->isBuilt())
	{
		this->triangleFadeHud->lazyGet()->resetAnim();
	}

	this->resetScreen->setOpacity(255);
	this->resetScreen->runAction(FadeTo::create(0.25f, 0));
}
