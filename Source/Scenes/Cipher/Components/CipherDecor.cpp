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

#include "Strings/Cipher/CipherCaps.h"

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
	this->inputStuds = std::vector<cocos2d::Sprite*>();
	this->outputStuds = std::vector<cocos2d::Sprite*>();

	LocalizedLabel* tempCipherLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::M2, Strings::Cipher_CipherCaps::create());

	tempCipherLabel->enableShadow(Color4B::BLACK, Size(4, -4), 4);
	tempCipherLabel->setTextColor(Color4B(102, 102, 102, 255));

	// Important: Render the label to a sprite or the shader effects will be deeply broken
	const Size padding = Size(32.0f, 32.0f);
	this->cipherLabel = RenderUtils::renderNodeToSprite(tempCipherLabel, -Vec2(tempCipherLabel->getContentSize()) / 2.0f, tempCipherLabel->getContentSize(), padding);
	tempCipherLabel = nullptr;

	RenderUtils::applyShader(this->cipherLabel, ShaderResources::Vertex_Cipher_Disort, ShaderResources::Fragment_Cipher_Disort);

	for (int index = 0; index < Config::MaxInputOutputCount; index++)
	{
		this->inputStuds.push_back(Sprite::create(CipherResources::Decor_Stud));
		this->outputStuds.push_back(Sprite::create(CipherResources::Decor_Stud));
	}

	for (auto it = this->inputStuds.begin(); it != this->inputStuds.end(); it++)
	{
		this->addChild(*it);
	}

	for (auto it = this->outputStuds.begin(); it != this->outputStuds.end(); it++)
	{
		this->addChild(*it);
	}

	this->addChild(this->furnace);
	
	this->addChild(this->logo);
	this->addChild(this->cipherLabel);
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

	int index = 0;

	for (auto it = this->inputStuds.begin(); it != this->inputStuds.end(); it++, index++)
	{
		(*it)->setPosition(Vec2(visibleSize.width / 2.0f + Config::LeftColumnCenter + float(index - Config::MaxInputOutputCount / 2) * Config::IOSpacing, visibleSize.height / 2.0f + Config::IOVerticalOffset + 24.0f));
	}

	index = 0;

	for (auto it = this->outputStuds.begin(); it != this->outputStuds.end(); it++, index++)
	{
		(*it)->setPosition(Vec2(visibleSize.width / 2.0f + Config::LeftColumnCenter + float(index - Config::MaxInputOutputCount / 2) * Config::IOSpacing, visibleSize.height / 2.0f - Config::IOVerticalOffset - 24.0f));
	}

	this->furnace->setPosition(Vec2(visibleSize.width / 2.0f + Config::LeftColumnCenter + 478.0f, visibleSize.height / 2.0f - 394.0f));
	this->logo->setPosition(Vec2(visibleSize.width / 2.0f + Config::LeftColumnCenter + 16.0f, visibleSize.height / 2.0f + 456.0f + 16.0f));
	this->cipherLabel->setPosition(Vec2(visibleSize.width / 2.0f + Config::LeftColumnCenter, visibleSize.height / 2.0f + 456.0f));
}

void CipherDecor::onBeforeStateChange(CipherState* cipherState)
{
	super::onBeforeStateChange(cipherState);
}

void CipherDecor::onAnyStateChange(CipherState* cipherState)
{
	super::onAnyStateChange(cipherState);
}
