#include "CipherDecor.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Utils/RenderUtils.h"
#include "Scenes/Cipher/Config.h"
#include "Scenes/Cipher/CipherState.h"

#include "Resources/CipherResources.h"
#include "Resources/ShaderResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

CipherDecor* CipherDecor::create()
{
	CipherDecor* instance = new CipherDecor();

	instance->autorelease();

	return instance;
}

CipherDecor::CipherDecor()
{
	this->furnace = Sprite::create(CipherResources::Decor_Furnace);
	this->logo = Sprite::create(CipherResources::Logo);

	LocalizedLabel* tempCipherLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::M2, Strings::Cipher_CipherCaps::create());

	tempCipherLabel->enableShadow(Color4B::BLACK, Size(4, -4), 4);
	tempCipherLabel->setTextColor(Color4B(102, 102, 102, 255));

	// Important: Render the label to a sprite or the shader effects will be deeply broken
	const Size padding = Size(32.0f, 32.0f);
	this->cipherLabel = RenderUtils::renderNodeToSprite(tempCipherLabel, -Vec2(tempCipherLabel->getContentSize()) / 2.0f, tempCipherLabel->getContentSize(), padding);
	tempCipherLabel = nullptr;

	if (this->cipherLabel != nullptr)
	{
		RenderUtils::applyShader(this->cipherLabel, ShaderResources::Vertex_Cipher_Disort, ShaderResources::Fragment_Cipher_Disort);
	}

	this->addChild(this->furnace);
	this->addChild(this->logo);
	
	if (this->cipherLabel != nullptr)
	{
		this->addChild(this->cipherLabel);
	}
}

CipherDecor::~CipherDecor()
{
}

void CipherDecor::onEnter()
{
	super::onEnter();
}

void CipherDecor::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->furnace->setPosition(Vec2(visibleSize.width / 2.0f + Config::LeftColumnCenter + 492.0f, visibleSize.height / 2.0f - 394.0f));
	this->logo->setPosition(Vec2(visibleSize.width / 2.0f + Config::LeftColumnCenter + 16.0f, visibleSize.height / 2.0f + 456.0f + 16.0f));
	this->cipherLabel->setPosition(Vec2(visibleSize.width / 2.0f + Config::LeftColumnCenter, visibleSize.height / 2.0f + 456.0f));
}

void CipherDecor::onAnyStateChange(CipherState* cipherState)
{
	super::onAnyStateChange(cipherState);
}
