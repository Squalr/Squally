#include "Lexicon.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Events/HackableEvents.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Hackables/CodeEditor/Lexicon/Pages/LexiconPages.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Localization/LocalizedSprite.h"
#include "Engine/Utils/GameUtils.h"

#include "Resources/UIResources.h"

#include "Strings/Menus/Return.h"

using namespace cocos2d;

Lexicon* Lexicon::create()
{
	Lexicon* instance = new Lexicon();

	instance->autorelease();

	return instance;
}

Lexicon::Lexicon()
{
	this->closeCallback = nullptr;
	this->leftPages = std::vector<LexiconPage*>();
	this->rightPages = std::vector<LexiconPage*>();

	this->background = Sprite::create(UIResources::Menus_LexiconMenu_desert_background);
	this->banner = Sprite::create(UIResources::Menus_LexiconMenu_Banner);
	this->title = LocalizedSprite::create(UIResources::Menus_LexiconMenu_Title_Lexicon_en);
	this->lexiconBack = Sprite::create(UIResources::Menus_LexiconMenu_LexiconBack);
	this->lexiconFront = Sprite::create(UIResources::Menus_LexiconMenu_LexiconFront);
	this->leftPageNode = Node::create();
	this->rightPageNode = Node::create();

	LocalizedLabel*	backLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_Return::create());
	LocalizedLabel*	backLabelSelected = backLabel->clone();

	backLabel->enableOutline(Color4B::BLACK, 2);
	backLabelSelected->enableOutline(Color4B::BLACK, 2);

	this->backButton = ClickableTextNode::create(backLabel, backLabelSelected, UIResources::Menus_Buttons_GenericButton, UIResources::Menus_Buttons_GenericButtonHover);
	this->darkFrame = Sprite::create(UIResources::Menus_LexiconMenu_DarkFrame);

	// Intro
	this->leftPages.push_back(IntroPage::create());
	this->rightPages.push_back(ChapterSelectPage::create());

	// Chapters
	this->leftPages.push_back(DataIntroPage::create());
	this->leftPages.push_back(BinaryIntroPage::create());
	this->leftPages.push_back(ControlFlowIntroPage::create());
	this->leftPages.push_back(VectorIntroPage::create());
	this->leftPages.push_back(FloatingPointIntroPage::create());

	// Data
	
	// Binary

	// Control flow
	this->leftPages.push_back(NopPage::create());

	// SIMD

	// FPU

	for (auto it = this->leftPages.begin(); it != this->leftPages.end(); it++)
	{
		this->leftPageNode->addChild(*it);
	}

	for (auto it = this->rightPages.begin(); it != this->rightPages.end(); it++)
	{
		this->rightPageNode->addChild(*it);
	}

	this->addChild(this->background);
	this->addChild(this->banner);
	this->addChild(this->title);
	this->addChild(this->lexiconBack);
	this->addChild(this->lexiconFront);
	this->addChild(this->leftPageNode);
	this->addChild(this->rightPageNode);
	this->addChild(this->darkFrame);
	this->addChild(this->backButton);
}

Lexicon::~Lexicon()
{
}

void Lexicon::onEnter()
{
	super::onEnter();

	HackableEvents::TriggerOpenLexiconPage(HackableEvents::OpenLexiconPageArgs(IntroPage::KeyIntroPage));
	HackableEvents::TriggerOpenLexiconPage(HackableEvents::OpenLexiconPageArgs(ChapterSelectPage::KeyChapterSelectPage));
}

void Lexicon::initializePositions()
{
	super::initializePositions();

	const Vec2 BookOffset = Vec2(32.0f, -48.0f);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	this->background->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->banner->setPosition(Vec2(visibleSize.width / 2.0f - 712.0f, visibleSize.height / 2.0f + 32.0f));
	this->title->setPosition(Vec2(visibleSize.width / 2.0f - 712.0f, visibleSize.height / 2.0f + 464.0f));
	this->backButton->setPosition(Vec2(visibleSize.width / 2.0f - 788.0f, 96.0f));
	this->lexiconBack->setPosition(Vec2(visibleSize.width / 2.0f + BookOffset.x, visibleSize.height / 2.0f + BookOffset.y));
	this->lexiconFront->setPosition(Vec2(visibleSize.width / 2.0f + BookOffset.x, visibleSize.height / 2.0f + BookOffset.y + 24.0f));
	this->leftPageNode->setPosition(Vec2(visibleSize.width / 2.0f + BookOffset.x - 324.0f, visibleSize.height / 2.0f + BookOffset.y + 36.0f));
	this->rightPageNode->setPosition(Vec2(visibleSize.width / 2.0f + BookOffset.x + 324.0f, visibleSize.height / 2.0f + BookOffset.y + 36.0f));
	this->darkFrame->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
}
	
void Lexicon::initializeListeners()
{
	super::initializeListeners();

	this->backButton->setMouseClickCallback([=](MouseEvents::MouseEventArgs*)
	{
		this->close();
	});
}

void Lexicon::open()
{
	this->setVisible(true);
	GameUtils::focus(this);
}

void Lexicon::close()
{
	if (this->isVisible())
	{
		if (closeCallback != nullptr)
		{
			closeCallback();
		}
		
		this->setVisible(false);
	}
}

void Lexicon::setCloseCallBack(std::function<void()> closeCallback)
{
	this->closeCallback = closeCallback;
}
