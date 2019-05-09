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
#include "Scenes/Cipher/CipherMenu/ChapterSelect/CipherChapterPreview.h"

#include "Resources/CipherResources.h"
#include "Resources/ParticleResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Cipher/SelectAChapter.h"
#include "Strings/Generics/Empty.h"
#include "Strings/Menus/Back.h"

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
	this->chapters = std::vector<CipherChapterPreview*>();
	
	LocalizedLabel* backButtonLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Back::create());
	LocalizedLabel* backButtonLabelHover = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Back::create());

	backButtonLabel->enableOutline(Color4B::BLACK, 2);
	backButtonLabelHover->enableOutline(Color4B::BLACK, 2);

	this->nether = ParticleSystemQuad::create(ParticleResources::BlueNether);
	this->swirl = ParticleSystemQuad::create(ParticleResources::BlueStarCircle);
	this->backboard = Sprite::create(CipherResources::Menus_CipherBackboard);
	this->chapterEndianForest = CipherChapterPreview::create("CIPHER_CHAPTER_ENDIAN_FOREST", CipherResources::Menus_EndianForest_Emblem, CipherResources::Menus_EndianForest_EmblemSelected, CipherResources::Menus_EndianForest_EmblemDisabled);
	this->chapterUnderflowRuins = CipherChapterPreview::create("CIPHER_CHAPTER_UNDERFLOW_RUINS", CipherResources::Menus_UnderflowRuins_Emblem, CipherResources::Menus_UnderflowRuins_EmblemSelected, CipherResources::Menus_UnderflowRuins_EmblemDisabled);
	this->chapterSeaSharpCaverns = CipherChapterPreview::create("CIPHER_CHAPTER_SEA_SHARP_CAVERNS", CipherResources::Menus_SeaSharpCaverns_Emblem, CipherResources::Menus_SeaSharpCaverns_EmblemSelected, CipherResources::Menus_SeaSharpCaverns_EmblemDisabled);
	this->chapterCastleValgrind = CipherChapterPreview::create("CIPHER_CHAPTER_CASTLE_VALGRIND", CipherResources::Menus_CastleValgrind_Emblem, CipherResources::Menus_CastleValgrind_EmblemSelected, CipherResources::Menus_CastleValgrind_EmblemDisabled);
	this->chapterBalmerPeaks = CipherChapterPreview::create("CIPHER_CHAPTER_BALMER_PEAKS", CipherResources::Menus_BalmerPeaks_Emblem, CipherResources::Menus_BalmerPeaks_EmblemSelected, CipherResources::Menus_BalmerPeaks_EmblemDisabled);
	this->chapterDaemonsHallow = CipherChapterPreview::create("CIPHER_CHAPTER_DAEMONS_HALLOW", CipherResources::Menus_DaemonsHallow_Emblem, CipherResources::Menus_DaemonsHallow_EmblemSelected, CipherResources::Menus_DaemonsHallow_EmblemDisabled);
	this->chapterLambdaCrypts = CipherChapterPreview::create("CIPHER_CHAPTER_LAMBDA_PEAKS", CipherResources::Menus_LambdaCrypts_Emblem, CipherResources::Menus_LambdaCrypts_EmblemSelected, CipherResources::Menus_LambdaCrypts_EmblemDisabled);
	this->chapterVoidStar = CipherChapterPreview::create("CIPHER_CHAPTER_VOID_STAR", CipherResources::Menus_VoidStar_Emblem, CipherResources::Menus_VoidStar_EmblemSelected, CipherResources::Menus_VoidStar_EmblemDisabled);
	this->titleLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H1, Strings::Cipher_SelectAChapter::create());
	this->backButton = ClickableTextNode::create(
		backButtonLabel,
		backButtonLabelHover,
		UIResources::Menus_Buttons_GenericButton,
		UIResources::Menus_Buttons_GenericButtonHover
	);

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
	this->addChild(this->backboard);

	for (auto it = this->chapters.begin(); it != this->chapters.end(); ++it)
	{
		this->addChild(*it);
	}
	this->addChild(this->titleLabel);
	this->addChild(this->backButton);
}

CipherChapterSelectMenu::~CipherChapterSelectMenu()
{
}

void CipherChapterSelectMenu::onEnter()
{
	super::onEnter();

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

	// Kinda looks shitty, disabling for now
	this->backboard->setVisible(false);

	this->loadLevels();
}

void CipherChapterSelectMenu::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	
	this->nether->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->swirl->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->backboard->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f - 80.0f));

	this->titleLabel->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height - 128.0f));
	this->backButton->setPosition(Vec2(visibleSize.width / 2.0f - 756.0f, visibleSize.height - 64.0f));

	int index = 0;

	for (auto it = this->chapters.begin(); it != this->chapters.end(); ++it)
	{
		int x = index % 4;
		int y = index / 4;

		(*it)->setPosition(Vec2((float(x) - 1.5f) * 320.0f + visibleSize.width / 2.0f, (float(y) - 0.5f) * -356.0f + visibleSize.height / 2.0f - 80.0f));

		index++;
	}
}

void CipherChapterSelectMenu::initializeListeners()
{
	super::initializeListeners();

	CipherChapterSelectMenu::instance->addGlobalEventListener(EventListenerCustom::create(NavigationEvents::EventNavigateCipherChapterSelect, [](EventCustom* args)
	{
		GlobalDirector::loadScene(CipherChapterSelectMenu::instance);
	}));

	this->backButton->setMouseClickCallback(CC_CALLBACK_0(CipherChapterSelectMenu::onCloseClick, this));
	this->backButton->setClickSound(SoundResources::ClickBack1);

	EventListenerKeyboard* keyboardListener = EventListenerKeyboard::create();

	keyboardListener->onKeyPressed = CC_CALLBACK_2(CipherChapterSelectMenu::onKeyPressed, this);

	this->chapterEndianForest->setClickCallback([=]()
	{
		NavigationEvents::navigateCipherPuzzleSelect(NavigationEvents::NavigateCipherPuzzleSelectArgs(NavigationEvents::NavigateCipherPuzzleSelectArgs::Chapter::EndianForest));
	});
	this->chapterUnderflowRuins->setClickCallback([=]()
	{
		NavigationEvents::navigateCipherPuzzleSelect(NavigationEvents::NavigateCipherPuzzleSelectArgs(NavigationEvents::NavigateCipherPuzzleSelectArgs::Chapter::UnderflowRuins));
	});
	this->chapterSeaSharpCaverns->setClickCallback([=]()
	{
		NavigationEvents::navigateCipherPuzzleSelect(NavigationEvents::NavigateCipherPuzzleSelectArgs(NavigationEvents::NavigateCipherPuzzleSelectArgs::Chapter::SeaSharpCaverns));
	});
	this->chapterCastleValgrind->setClickCallback([=]()
	{
		NavigationEvents::navigateCipherPuzzleSelect(NavigationEvents::NavigateCipherPuzzleSelectArgs(NavigationEvents::NavigateCipherPuzzleSelectArgs::Chapter::CastleValgrind));
	});
	this->chapterBalmerPeaks->setClickCallback([=]()
	{
		NavigationEvents::navigateCipherPuzzleSelect(NavigationEvents::NavigateCipherPuzzleSelectArgs(NavigationEvents::NavigateCipherPuzzleSelectArgs::Chapter::BalmerPeaks));
	});
	this->chapterDaemonsHallow->setClickCallback([=]()
	{
		NavigationEvents::navigateCipherPuzzleSelect(NavigationEvents::NavigateCipherPuzzleSelectArgs(NavigationEvents::NavigateCipherPuzzleSelectArgs::Chapter::DaemonsHallow));
	});
	this->chapterLambdaCrypts->setClickCallback([=]()
	{
		NavigationEvents::navigateCipherPuzzleSelect(NavigationEvents::NavigateCipherPuzzleSelectArgs(NavigationEvents::NavigateCipherPuzzleSelectArgs::Chapter::LambdaCrypts));
	});
	this->chapterVoidStar->setClickCallback([=]()
	{
		NavigationEvents::navigateCipherPuzzleSelect(NavigationEvents::NavigateCipherPuzzleSelectArgs(NavigationEvents::NavigateCipherPuzzleSelectArgs::Chapter::VoidStar));
	});

	this->addEventListener(keyboardListener);
}

void CipherChapterSelectMenu::loadLevels()
{
	// Disable all
	for (auto it = this->chapters.begin(); it != this->chapters.end(); ++it)
	{
		(*it)->enableInteraction();
	}

	// Enable first
	for (auto it = this->chapters.begin(); it != this->chapters.end(); ++it)
	{
		(*it)->enableInteraction();
		break;
	}

	std::vector<CipherChapterPreview*>::iterator prevIt = this->chapters.begin();

	for (auto it = this->chapters.begin(); it != this->chapters.end(); prevIt = it, ++it)
	{
		if ((*prevIt)->isChapterCleared())
		{
			(*it)->enableInteraction();
		}
	}
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
