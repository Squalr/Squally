#include "CipherChapterSelectMenu.h"

#include "cocos/2d/CCParticleSystemQuad.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCEventListenerKeyboard.h"

#include "Engine/GlobalDirector.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Utils/GameUtils.h"
#include "Events/NavigationEvents.h"

#include "Resources/CipherResources.h"
#include "Resources/ParticleResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Hexus/HexusPuzzles.h"
#include "Strings/Generics/Empty.h"

using namespace cocos2d;

CipherChapterSelectMenu* CipherChapterSelectMenu::instance = nullptr;
const Color3B CipherChapterSelectMenu::TitleColor = Color3B(88, 188, 193);

void CipherChapterSelectMenu::registerGlobalScene()
{
	if (CipherChapterSelectMenu::instance == nullptr)
	{
		CipherChapterSelectMenu::instance = new CipherChapterSelectMenu();

		CipherChapterSelectMenu::instance->autorelease();
		CipherChapterSelectMenu::instance->initializeListeners();
	}

	GlobalDirector::registerGlobalScene(CipherChapterSelectMenu::instance);
}

CipherChapterSelectMenu::CipherChapterSelectMenu()
{
	this->chapters = std::vector<ClickableNode*>();

	this->titleLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H2, Strings::Hexus_HexusPuzzles::create());
	this->backButton = ClickableNode::create(UIResources::Menus_Buttons_CloseButton, UIResources::Menus_Buttons_CloseButtonHover);
	this->chapterEndianForest = ClickableNode::create(CipherResources::Menus_EndianForest_Emblem, CipherResources::Menus_EndianForest_Emblem);
	this->chapterUnderflowRuins = ClickableNode::create(CipherResources::Menus_UnderflowRuins_Emblem, CipherResources::Menus_UnderflowRuins_Emblem);
	this->chapterSeaSharpCaverns = ClickableNode::create(CipherResources::Menus_SeaSharpCaverns_Emblem, CipherResources::Menus_SeaSharpCaverns_Emblem);
	this->chapterCastleValgrind = ClickableNode::create(CipherResources::Menus_CastleValgrind_Emblem, CipherResources::Menus_CastleValgrind_Emblem);
	this->chapterBalmerPeaks = ClickableNode::create(CipherResources::Menus_BalmerPeaks_Emblem, CipherResources::Menus_BalmerPeaks_Emblem);
	this->chapterDaemonsHallow = ClickableNode::create(CipherResources::Menus_DaemonsHallow_Emblem, CipherResources::Menus_DaemonsHallow_Emblem);
	this->chapterLambdaCrypts = ClickableNode::create(CipherResources::Menus_LambdaCrypts_Emblem, CipherResources::Menus_LambdaCrypts_Emblem);
	this->chapterVoidStar = ClickableNode::create(CipherResources::Menus_VoidStar_Emblem, CipherResources::Menus_VoidStar_Emblem);

	this->nether = ParticleSystemQuad::create(ParticleResources::BlueNether);
	this->swirl = ParticleSystemQuad::create(ParticleResources::BlueStarCircle);

	this->titleLabel->setColor(CipherChapterSelectMenu::TitleColor);
	this->titleLabel->enableShadow(Color4B::BLACK, Size(2, -2), 2);

	this->chapters.push_back(this->chapterEndianForest);
	this->chapters.push_back(this->chapterUnderflowRuins);
	this->chapters.push_back(this->chapterSeaSharpCaverns);
	this->chapters.push_back(this->chapterCastleValgrind);
	this->chapters.push_back(this->chapterBalmerPeaks);
	this->chapters.push_back(this->chapterDaemonsHallow);
	this->chapters.push_back(this->chapterLambdaCrypts);
	this->chapters.push_back(this->chapterVoidStar);

	this->addChild(this->nether);
	this->addChild(this->swirl);

	this->addChild(this->titleLabel);
	this->addChild(this->backButton);

	this->backButton->setMouseClickCallback(CC_CALLBACK_0(CipherChapterSelectMenu::onCloseClick, this));
	this->backButton->setClickSound(SoundResources::ClickBack1);

	for (auto it = this->chapters.begin(); it != this->chapters.end(); ++it)
	{
		this->addChild(*it);
	}
}

CipherChapterSelectMenu::~CipherChapterSelectMenu()
{
}

void CipherChapterSelectMenu::onEnter()
{
	GlobalScene::onEnter();

	float delay = 0.25f;
	float duration = 0.35f;

	GameUtils::fadeInObject(this->titleLabel, delay, duration);
	GameUtils::fadeInObject(this->backButton, delay, duration);

	for (auto it = this->chapters.begin(); it != this->chapters.end(); ++it)
	{
		GameUtils::fadeInObject(*it, delay, duration);
	}

	// Initialize particles to an intermediate state
	GameUtils::accelerateParticles(this->swirl, 5.0f);
	GameUtils::accelerateParticles(this->nether, 1.0f);
}

void CipherChapterSelectMenu::initializePositions()
{
	GlobalScene::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	
	this->nether->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->swirl->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));

	this->titleLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 248.0f));
	this->backButton->setPosition(Vec2(visibleSize.width / 2 + 308.0f, visibleSize.height / 2 + 222.0f));

	int index = 0;

	for (auto it = this->chapters.begin(); it != this->chapters.end(); ++it)
	{
		int x = index % 4;
		int y = index / 4;

		(*it)->setPosition(Vec2(float(x - 2) * 128.0f + visibleSize.width / 2.0f, (float(y) + 0.5f) * -128.0f + visibleSize.height));
	}
}

void CipherChapterSelectMenu::initializeListeners()
{
	GlobalScene::initializeListeners();

	CipherChapterSelectMenu::instance->addGlobalEventListener(EventListenerCustom::create(NavigationEvents::EventNavigateCipherChapterSelect, [](EventCustom* args)
	{
		GlobalDirector::loadScene(CipherChapterSelectMenu::instance);
	}));

	EventListenerKeyboard* keyboardListener = EventListenerKeyboard::create();

	keyboardListener->onKeyPressed = CC_CALLBACK_2(CipherChapterSelectMenu::onKeyPressed, this);

	this->addEventListener(keyboardListener);
}

void CipherChapterSelectMenu::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
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
			NavigationEvents::navigateBack();
			break;
		}
		default:
		{
			break;
		}
	}
}

void CipherChapterSelectMenu::onCloseClick()
{
	NavigationEvents::navigateBack();
}
