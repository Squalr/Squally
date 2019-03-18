#include "Cipher.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCEventListenerKeyboard.h"

#include "Engine/Config/ConfigManager.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/RenderUtils.h"
#include "Events/CipherEvents.h"
#include "Menus/Options/GeneralTab.h"
#include "Menus/Options/LanguageTab.h"
#include "Menus/Options/MemesTab.h"
#include "Menus/Options/VideoTab.h"

#include "Resources/ShaderResources.h"
#include "Resources/CipherResources.h"

#include "Strings/Cipher/CipherCaps.h"
#include "Strings/Cipher/Execute.h"
#include "Strings/Cipher/Inputs.h"
#include "Strings/Cipher/Outputs.h"
#include "Strings/Cipher/Tools.h"
#include "Strings/Menus/Cancel.h"
#include "Strings/Menus/Return.h"

using namespace cocos2d;

const Color3B Cipher::TitleColor = Color3B(88, 188, 193);

Cipher* Cipher::create()
{
	Cipher* instance = new Cipher();

	instance->autorelease();

	return instance;
}

Cipher::Cipher()
{
	this->backClickCallback = nullptr;

	this->cipherWindow = Sprite::create(CipherResources::CipherMenu);
	this->leftPanel = Node::create();
	this->rightPanel = Node::create();
	Label* tempCipherLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::M1, Strings::Cipher_CipherCaps::create());
	this->cipherToolsLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H1, Strings::Cipher_Tools::create());
	this->inputsLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Cipher_Inputs::create());
	this->outputsLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Cipher_Outputs::create());
	
	this->inputsLabel->enableShadow(Color4B::BLACK, Size(2, -2), 2);
	this->outputsLabel->enableShadow(Color4B::BLACK, Size(2, -2), 2);
	this->cipherToolsLabel->enableShadow(Color4B::BLACK, Size(2, -2), 2);

	tempCipherLabel->enableShadow(Color4B::BLACK, Size(4, -4), 4);
	tempCipherLabel->setTextColor(Color4B(102, 102, 102, 255));

	// Important: Render the label to a sprite or the shader effects will be deeply broken
	const Size padding = Size(32.0f, 32.0f);
	this->cipherLabel = RenderUtils::renderNodeToSprite(tempCipherLabel, -Vec2(tempCipherLabel->getContentSize()) / 2.0f, tempCipherLabel->getContentSize(), padding);
	tempCipherLabel = nullptr;

	RenderUtils::applyShader(this->cipherLabel, ShaderResources::Vertex_Cipher_Disort, ShaderResources::Fragment_Cipher_Disort, [=](GLProgramState* state)
	{
	});

	this->toggleButtonBin = ClickableNode::create(CipherResources::BinaryButton, CipherResources::BinaryButtonSelected);
	this->toggleButtonDec = ClickableNode::create(CipherResources::DecimalButton, CipherResources::DecimalButtonSelected);
	this->toggleButtonHex = ClickableNode::create(CipherResources::HexButton, CipherResources::HexButtonSelected);
	this->toggleButtonAscii = ClickableNode::create(CipherResources::AsciiButton, CipherResources::AsciiButtonSelected);
	this->viewAsciiTableButton = ClickableNode::create(CipherResources::AsciiTableButton, CipherResources::AsciiTableButtonSelected);

	LocalizedLabel*	executeLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Cipher_Execute::create());
	LocalizedLabel*	executeLabelHover = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Cipher_Execute::create());

	executeLabel->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	executeLabel->enableGlow(Color4B::BLACK);

	executeLabelHover->setColor(Color3B::YELLOW);
	executeLabelHover->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	executeLabelHover->enableGlow(Color4B::ORANGE);

	this->executeButton = ClickableTextNode::create(
		executeLabel,
		executeLabelHover,
		CipherResources::RunButton,
		CipherResources::RunButtonSelected);

	LocalizedLabel*	quitLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Return::create());
	LocalizedLabel*	quitLabelHover = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Return::create());

	quitLabel->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	quitLabel->enableGlow(Color4B::BLACK);

	quitLabelHover->setColor(Color3B::YELLOW);
	quitLabelHover->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	quitLabelHover->enableGlow(Color4B::ORANGE);

	this->quitButton = ClickableTextNode::create(
		quitLabel,
		quitLabelHover,
		CipherResources::QuitButton,
		CipherResources::QuitButtonSelected);

	this->leftPanel->addChild(this->cipherLabel);
	this->leftPanel->addChild(this->inputsLabel);
	this->leftPanel->addChild(this->outputsLabel);
	this->leftPanel->addChild(this->toggleButtonBin);
	this->leftPanel->addChild(this->toggleButtonDec);
	this->leftPanel->addChild(this->toggleButtonHex);
	this->leftPanel->addChild(this->toggleButtonAscii);
	this->leftPanel->addChild(this->viewAsciiTableButton);
	this->leftPanel->addChild(this->executeButton);

	this->rightPanel->addChild(this->quitButton);
	this->rightPanel->addChild(this->cipherToolsLabel);

	this->addChild(this->cipherWindow);
	this->addChild(this->leftPanel);
	this->addChild(this->rightPanel);
}

Cipher::~Cipher()
{
}

void Cipher::onEnter()
{
	super::onEnter();

	this->setVisible(false);
}

void Cipher::initializeListeners()
{
	super::initializeListeners();

	this->quitButton->setClickCallback([=](ClickableNode*, MouseEvents::MouseEventArgs*) { this->onMenuExit();  });

	EventListenerKeyboard* keyboardListener = EventListenerKeyboard::create();

	keyboardListener->onKeyPressed = CC_CALLBACK_2(Cipher::onKeyPressed, this);

	this->addEventListener(keyboardListener);
}

void Cipher::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->cipherWindow->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->leftPanel->setPosition(Vec2(visibleSize.width / 2.0f - 248.0f, visibleSize.height / 2.0f));
	this->rightPanel->setPosition(Vec2(visibleSize.width / 2.0f + 712.0f, visibleSize.height / 2.0f));

	// Left panel
	this->cipherLabel->setPosition(0.0f, 420.0f);
	this->inputsLabel->setPosition(-476.0f, 422.0f);
	this->outputsLabel->setPosition(476.0f, 422.0f);
	this->toggleButtonBin->setPosition(Vec2(-518.0f + 64.0f * 0.0f, -432.0f));
	this->toggleButtonDec->setPosition(Vec2(-518.0f + 64.0f * 1.0f, -432.0f));
	this->toggleButtonHex->setPosition(Vec2(-518.0f + 64.0f * 2.0f, -432.0f));
	this->toggleButtonAscii->setPosition(Vec2(-518.0f + 64.0f * 3.0f, -432.0f));
	this->viewAsciiTableButton->setPosition(Vec2(420.0f, -420.0f));
	this->executeButton->setPosition(Vec2(0.0f, -420.0f));
	
	// Right panel
	this->cipherToolsLabel->setPosition(0.0f, 450.0f);
	this->quitButton->setPosition(Vec2(0.0f, -420.0f));
}

void Cipher::setBackClickCallback(std::function<void()> backClickCallback)
{
	this->backClickCallback = backClickCallback;
}

void Cipher::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (!GameUtils::isVisible(this))
	{
		return;
	}

	switch (keyCode)
	{
		case EventKeyboard::KeyCode::KEY_ESCAPE:
		{
			event->stopPropagation();
			this->onMenuExit();
			break;
		}
		default:
		{
			break;
		}
	}
}

void Cipher::onMenuExit()
{
	ConfigManager::save();

	if (this->backClickCallback != nullptr)
	{
		this->backClickCallback();
	}
}
