#include "CipherBackground.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Utils/RenderUtils.h"
#include "Scenes/Cipher/Config.h"
#include "Scenes/Cipher/Components/Blocks/XorBlock.h"
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
	this->cipherWindow = Sprite::create(CipherResources::CipherMenu);

	LocalizedLabel* tempCipherLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::M1, Strings::Cipher_CipherCaps::create());

	tempCipherLabel->enableShadow(Color4B::BLACK, Size(4, -4), 4);
	tempCipherLabel->setTextColor(Color4B(102, 102, 102, 255));

	// Important: Render the label to a sprite or the shader effects will be deeply broken
	const Size padding = Size(32.0f, 32.0f);
	this->cipherLabel = RenderUtils::renderNodeToSprite(tempCipherLabel, -Vec2(tempCipherLabel->getContentSize()) / 2.0f, tempCipherLabel->getContentSize(), padding);
	tempCipherLabel = nullptr;

	RenderUtils::applyShader(this->cipherLabel, ShaderResources::Vertex_Cipher_Disort, ShaderResources::Fragment_Cipher_Disort, [=](GLProgramState* state)
	{
	});

	this->addChild(this->cipherWindow);
	this->addChild(this->cipherLabel);
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

	this->cipherWindow->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->cipherLabel->setPosition(Vec2(visibleSize.width / 2.0f + Config::LeftColumnCenter, visibleSize.height / 2.0f + 420.0f));
}

void CipherBackground::onBeforeStateChange(CipherState* cipherState)
{
	super::onBeforeStateChange(cipherState);
}

void CipherBackground::onAnyStateChange(CipherState* cipherState)
{
	super::onAnyStateChange(cipherState);
}
