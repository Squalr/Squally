#include "CipherStateTransitionNeutral.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCClippingNode.h"
#include "cocos/2d/CCDrawNode.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Input/ClickableNode.h"
#include "Scenes/Cipher/Config.h"
#include "Scenes/Cipher/CipherState.h"

#include "Resources/CipherResources.h"

using namespace cocos2d;

CipherStateTransitionNeutral* CipherStateTransitionNeutral::create()
{
	CipherStateTransitionNeutral* instance = new CipherStateTransitionNeutral();

	instance->autorelease();

	return instance;
}

CipherStateTransitionNeutral::CipherStateTransitionNeutral() : super(CipherState::StateType::TransitionNeutral)
{
	DrawNode* stencil = DrawNode::create();

	stencil->drawSolidRect(Vec2(-224.0f, -224.0f), Vec2(224.0f, 224.0f), Color4F::GREEN);

	this->contentClip = ClippingNode::create(stencil);
	this->transitionPanel = Sprite::create(CipherResources::TransitionPanel);

	// Enable to debug clipping:
	// this->contentClip->addChild(stencil);

	this->contentClip->addChild(this->transitionPanel);
	this->addChild(this->contentClip);
}

CipherStateTransitionNeutral::~CipherStateTransitionNeutral()
{
}

void CipherStateTransitionNeutral::onEnter()
{
	super::onEnter();
	
	this->setVisible(false);
}

void CipherStateTransitionNeutral::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->contentClip->setPosition(Vec2(visibleSize.width / 2.0f + Config::RightColumnCenter, visibleSize.height / 2.0f + Config::TopPanelCenter));
}

void CipherStateTransitionNeutral::initializeListeners()
{
	super::initializeListeners();
}

void CipherStateTransitionNeutral::onBeforeStateEnter(CipherState* cipherState)
{
	super::onBeforeStateEnter(cipherState);
}

void CipherStateTransitionNeutral::onStateEnter(CipherState* cipherState)
{
	super::onStateEnter(cipherState);
	
	this->transitionPanel->setPosition(Vec2(0.0f, 512.0f));
	this->setVisible(true);

	this->transitionPanel->runAction(Sequence::create(
		MoveTo::create(0.35f, Vec2(0.0f, 0.0f)),
		DelayTime::create(0.25f),
		CallFunc::create([=]()
		{
			cipherState->toolBoxPointer->setVisible(true);
			cipherState->lockPointer->setVisible(false);
		}),
		MoveTo::create(0.35f, Vec2(0.0f, 512.0f)),
		CallFunc::create([=]()
		{
			this->setVisible(false);
			CipherState::updateState(cipherState, CipherState::StateType::Neutral);
		}),
		nullptr
	));
}

void CipherStateTransitionNeutral::onStateReload(CipherState* cipherState)
{
	super::onStateReload(cipherState);
}

void CipherStateTransitionNeutral::onStateExit(CipherState* cipherState)
{
	super::onStateExit(cipherState);
}
