#include "CipherBackground.h"

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

CipherBackground* CipherBackground::create()
{
	CipherBackground* instance = new CipherBackground();

	instance->autorelease();

	return instance;
}

CipherBackground::CipherBackground()
{
	this->cipherBackground = Sprite::create(CipherResources::CipherMenuBase);

	this->addChild(this->cipherBackground);
}

CipherBackground::~CipherBackground()
{
}

void CipherBackground::onEnter()
{
	super::onEnter();
}

void CipherBackground::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->cipherBackground->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
}

void CipherBackground::onAnyStateChange(CipherState* cipherState)
{
	super::onAnyStateChange(cipherState);
}
