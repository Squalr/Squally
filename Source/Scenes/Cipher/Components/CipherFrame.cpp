#include "CipherFrame.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Utils/RenderUtils.h"
#include "Scenes/Cipher/Config.h"
#include "Scenes/Cipher/CipherState.h"

#include "Resources/CipherResources.h"
#include "Resources/ShaderResources.h"

#include "Strings/Cipher/CipherCaps.h"

using namespace cocos2d;

CipherFrame* CipherFrame::create()
{
	CipherFrame* instance = new CipherFrame();

	instance->autorelease();

	return instance;
}

CipherFrame::CipherFrame()
{
	this->cipherFrame = Sprite::create(CipherResources::CipherMenuFrame);

	this->addChild(this->cipherFrame);
}

CipherFrame::~CipherFrame()
{
}

void CipherFrame::onEnter()
{
	super::onEnter();
}

void CipherFrame::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->cipherFrame->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
}

void CipherFrame::onAnyStateChange(CipherState* cipherState)
{
	super::onAnyStateChange(cipherState);
}
