#include "HexusPuzzlesMenu.h"

HexusPuzzlesMenu* HexusPuzzlesMenu::instance = nullptr;
const Color3B HexusPuzzlesMenu::TitleColor = Color3B(88, 188, 193);
const std::string HexusPuzzlesMenu::StringKeyHexusPuzzles = "Menu_Hexus_Puzzles";

void HexusPuzzlesMenu::registerGlobalScene()
{
	if (HexusPuzzlesMenu::instance == nullptr)
	{
		HexusPuzzlesMenu::instance = new HexusPuzzlesMenu();

		HexusPuzzlesMenu::instance->autorelease();
		HexusPuzzlesMenu::instance->initializeListeners();
	}

	GlobalDirector::registerGlobalScene(HexusPuzzlesMenu::instance);
}

HexusPuzzlesMenu::HexusPuzzlesMenu()
{
	this->hexusOpponentItems = std::vector<HexusPuzzleItem*>();

	this->currentPage = 0;

	this->tutorialWindow = Sprite::create(UIResources::Menus_TutorialMenu_TutorialSelect);
	this->titleLabel = Label::create(Localization::resolveString(HexusPuzzlesMenu::StringKeyHexusPuzzles), Localization::getMainFont(), 32.0f);
	this->descriptionBox = Sprite::create(UIResources::Menus_TutorialMenu_TutorialItem);
	this->description = Label::create("", Localization::getMainFont(), 14.0f);
	this->closeButton = MenuSprite::create(UIResources::Menus_Buttons_CloseButton, UIResources::Menus_Buttons_CloseButtonHover);

	this->nether = ParticleSystemQuad::create(ParticleResources::BlueNether);
	this->swirl = ParticleSystemQuad::create(ParticleResources::BlueStarCircle);

	this->titleLabel->setColor(HexusPuzzlesMenu::TitleColor);
	this->titleLabel->enableShadow(Color4B::BLACK, Size(2, -2), 2);

	this->addChild(this->nether);
	this->addChild(this->swirl);

	this->addChild(this->tutorialWindow);
	this->addChild(this->titleLabel);
	this->addChild(this->closeButton);
	this->addChild(this->descriptionBox);
	this->addChild(this->description);

	this->loadLevels();

	this->closeButton->setClickCallback(CC_CALLBACK_1(HexusPuzzlesMenu::onCloseClick, this));
	this->closeButton->setClickSound(SoundResources::ClickBack1);

	for (std::vector<HexusPuzzleItem*>::iterator it = this->hexusOpponentItems.begin(); it != this->hexusOpponentItems.end(); ++it)
	{
		this->addChild(*it);
	}

	this->addChild(Mouse::create());
}

HexusPuzzlesMenu::~HexusPuzzlesMenu()
{
}

void HexusPuzzlesMenu::onEnter()
{
	GlobalScene::onEnter();

	float delay = 0.25f;
	float duration = 0.35f;

	GameUtils::fadeInObject(this->tutorialWindow, delay, duration);
	GameUtils::fadeInObject(this->titleLabel, delay, duration);
	GameUtils::fadeInObject(this->descriptionBox, delay, duration);
	GameUtils::fadeInObject(this->description, delay, duration);
	GameUtils::fadeInObject(this->closeButton, delay, duration);

	for (std::vector<HexusPuzzleItem*>::iterator it = this->hexusOpponentItems.begin(); it != this->hexusOpponentItems.end(); ++it)
	{
		GameUtils::fadeInObject(*it, delay, duration);
	}

	// Initialize particles to an intermediate state
	GameUtils::accelerateParticles(this->swirl, 5.0f);
	GameUtils::accelerateParticles(this->nether, 1.0f);
}

void HexusPuzzlesMenu::initializePositions()
{
	GlobalScene::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	
	this->nether->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->swirl->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));

	this->tutorialWindow->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->titleLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 248.0f));
	this->closeButton->setPosition(Vec2(visibleSize.width / 2 + 308.0f, visibleSize.height / 2 + 222.0f));
	this->descriptionBox->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 196.0f));
	this->description->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 196.0f));

	for (std::vector<HexusPuzzleItem*>::iterator it = this->hexusOpponentItems.begin(); it != this->hexusOpponentItems.end(); ++it)
	{
		(*it)->initializePositions();
	}
}

void HexusPuzzlesMenu::initializeListeners()
{
	GlobalScene::initializeListeners();

	HexusPuzzlesMenu::instance->addGlobalEventListener(EventListenerCustom::create(NavigationEvents::EventNavigateHexusPuzzles, [](EventCustom* args)
	{
		GlobalDirector::loadScene(HexusPuzzlesMenu::instance);
	}));

	EventListenerKeyboard* keyboardListener = EventListenerKeyboard::create();

	keyboardListener->onKeyPressed = CC_CALLBACK_2(HexusPuzzlesMenu::onKeyPressed, this);

	this->addEventListener(keyboardListener);
}

void HexusPuzzlesMenu::loadLevels()
{
	auto callback = CC_CALLBACK_1(HexusPuzzlesMenu::onMouseOver, this);
	int index = 0;

	this->hexusOpponentItems.push_back(HexusPuzzleItem::create(
		"Exact Value Scan I",
		MapResources::Tutorials_TutorialExactValueScan1_TutorialExactValueScan1,
		index++,
		callback
	));

	this->hexusOpponentItems.push_back(HexusPuzzleItem::create(
		"Exact Value Scan II",
		MapResources::Tutorials_TutorialExactValueScan1_TutorialExactValueScan1,
		index++,
		callback
	));

	this->hexusOpponentItems.push_back(HexusPuzzleItem::create(
		"Unknown Value Scan",
		MapResources::Tutorials_TutorialExactValueScan1_TutorialExactValueScan1,
		index++,
		callback
	));

	this->hexusOpponentItems.push_back(HexusPuzzleItem::create(
		"Data Types - Float",
		MapResources::Tutorials_TutorialExactValueScan1_TutorialExactValueScan1,
		index++,
		callback
	));

	this->hexusOpponentItems.push_back(HexusPuzzleItem::create(
		"Data Types - Double",
		MapResources::Tutorials_TutorialExactValueScan1_TutorialExactValueScan1,
		index++,
		callback
	));

	this->hexusOpponentItems.push_back(HexusPuzzleItem::create(
		"Godmode",
		MapResources::Tutorials_TutorialExactValueScan1_TutorialExactValueScan1,
		index++,
		callback
	));

	this->hexusOpponentItems.push_back(HexusPuzzleItem::create(
		"Position I",
		MapResources::Tutorials_TutorialExactValueScan1_TutorialExactValueScan1,
		index++,
		callback
	));

	this->hexusOpponentItems.push_back(HexusPuzzleItem::create(
		"Position II",
		MapResources::Tutorials_TutorialExactValueScan1_TutorialExactValueScan1,
		index++,
		callback
	));

	this->hexusOpponentItems.push_back(HexusPuzzleItem::create(
		"Blink Godmode I",
		MapResources::Tutorials_TutorialExactValueScan1_TutorialExactValueScan1,
		index++,
		callback
	));

	this->hexusOpponentItems.push_back(HexusPuzzleItem::create(
		"Blink Godmode II",
		MapResources::Tutorials_TutorialExactValueScan1_TutorialExactValueScan1,
		index++,
		callback
	));
}

void HexusPuzzlesMenu::onMouseOver(HexusPuzzleItem* tutorialItem)
{
	if (this->description->getString() != tutorialItem->tutorialDescription)
	{
		this->description->setString(tutorialItem->tutorialDescription);
	}
}

void HexusPuzzlesMenu::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (!GameUtils::isFocused(this))
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

void HexusPuzzlesMenu::onCloseClick(MenuSprite* menuSprite)
{
	NavigationEvents::navigateBack();
}
