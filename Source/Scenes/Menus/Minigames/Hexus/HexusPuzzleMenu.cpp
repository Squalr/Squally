#include "HexusPuzzlesMenu.h"

const Color3B HexusPuzzlesMenu::TitleColor = Color3B(88, 188, 193);
const std::string HexusPuzzlesMenu::StringKeyHexusPuzzles = "Menu_Hexus_Puzzles";

HexusPuzzlesMenu * HexusPuzzlesMenu::create()
{
	HexusPuzzlesMenu* instance = new HexusPuzzlesMenu();

	instance->autorelease();

	return instance;
}

HexusPuzzlesMenu::HexusPuzzlesMenu()
{
	this->hexusOpponentItems = new std::vector<HexusOpponentItem*>();

	this->currentPage = 0;

	this->tutorialWindow = Sprite::create(Resources::Menus_TutorialMenu_TutorialSelect);
	this->titleLabel = Label::create(Localization::resolveString(HexusPuzzlesMenu::StringKeyHexusPuzzles), Localization::getMainFont(), 32.0f);
	this->descriptionBox = Sprite::create(Resources::Menus_TutorialMenu_TutorialItem);
	this->description = Label::create("", Localization::getMainFont(), 14.0f);
	this->closeButton = MenuSprite::create(Resources::Menus_Buttons_CloseButton, Resources::Menus_Buttons_CloseButtonHover, Resources::Menus_Buttons_CloseButtonClick);

	this->nether = ParticleSystemQuad::create(Resources::Particles_BlueNether);
	this->swirl = ParticleSystemQuad::create(Resources::Particles_BlueStarCircle);

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
	this->closeButton->setClickSound(Resources::Sounds_ClickBack1);

	for (std::vector<HexusOpponentItem*>::iterator it = this->hexusOpponentItems->begin(); it != this->hexusOpponentItems->end(); ++it)
	{
		this->addChild(*it);
	}

	this->addChild(Mouse::create());

	this->initializeListeners();
}

HexusPuzzlesMenu::~HexusPuzzlesMenu()
{
}

void HexusPuzzlesMenu::onEnter()
{
	FadeScene::onEnter();

	float delay = 0.25f;
	float duration = 0.35f;

	GameUtils::fadeInObject(this->tutorialWindow, delay, duration);
	GameUtils::fadeInObject(this->titleLabel, delay, duration);
	GameUtils::fadeInObject(this->descriptionBox, delay, duration);
	GameUtils::fadeInObject(this->description, delay, duration);
	GameUtils::fadeInObject(this->closeButton, delay, duration);

	for (std::vector<HexusOpponentItem*>::iterator it = this->hexusOpponentItems->begin(); it != this->hexusOpponentItems->end(); ++it)
	{
		GameUtils::fadeInObject(*it, delay, duration);
	}

	// Initialize particles to an intermediate state
	GameUtils::accelerateParticles(this->swirl, 5.0f);
	GameUtils::accelerateParticles(this->nether, 1.0f);

	this->initializePositions();
}

void HexusPuzzlesMenu::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->nether->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->swirl->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));

	this->tutorialWindow->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->titleLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 248.0f));
	this->closeButton->setPosition(Vec2(origin.x + visibleSize.width / 2 + 308.0f, origin.y + visibleSize.height / 2 + 222.0f));
	this->descriptionBox->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - 196.0f));
	this->description->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - 196.0f));

	for (std::vector<HexusOpponentItem*>::iterator it = this->hexusOpponentItems->begin(); it != this->hexusOpponentItems->end(); ++it)
	{
		(*it)->initializePositions();
	}
}

void HexusPuzzlesMenu::loadLevels()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto callback = CC_CALLBACK_1(HexusPuzzlesMenu::onMouseOver, this);
	int index = 0;

	this->hexusOpponentItems->push_back(HexusOpponentItem::create(
		"Exact Value Scan I",
		Resources::Maps_Platformer_Tutorials_TutorialExactValueScan1_TutorialExactValueScan1,
		index++,
		callback
	));

	this->hexusOpponentItems->push_back(HexusOpponentItem::create(
		"Exact Value Scan II",
		Resources::Maps_Platformer_Tutorials_TutorialExactValueScan1_TutorialExactValueScan1,
		index++,
		callback
	));

	this->hexusOpponentItems->push_back(HexusOpponentItem::create(
		"Unknown Value Scan",
		Resources::Maps_Platformer_Tutorials_TutorialExactValueScan1_TutorialExactValueScan1,
		index++,
		callback
	));

	this->hexusOpponentItems->push_back(HexusOpponentItem::create(
		"Data Types - Float",
		Resources::Maps_Platformer_Tutorials_TutorialExactValueScan1_TutorialExactValueScan1,
		index++,
		callback
	));

	this->hexusOpponentItems->push_back(HexusOpponentItem::create(
		"Data Types - Double",
		Resources::Maps_Platformer_Tutorials_TutorialExactValueScan1_TutorialExactValueScan1,
		index++,
		callback
	));

	this->hexusOpponentItems->push_back(HexusOpponentItem::create(
		"Godmode",
		Resources::Maps_Platformer_Tutorials_TutorialExactValueScan1_TutorialExactValueScan1,
		index++,
		callback
	));

	this->hexusOpponentItems->push_back(HexusOpponentItem::create(
		"Position I",
		Resources::Maps_Platformer_Tutorials_TutorialExactValueScan1_TutorialExactValueScan1,
		index++,
		callback
	));

	this->hexusOpponentItems->push_back(HexusOpponentItem::create(
		"Position II",
		Resources::Maps_Platformer_Tutorials_TutorialExactValueScan1_TutorialExactValueScan1,
		index++,
		callback
	));

	this->hexusOpponentItems->push_back(HexusOpponentItem::create(
		"Blink Godmode I",
		Resources::Maps_Platformer_Tutorials_TutorialExactValueScan1_TutorialExactValueScan1,
		index++,
		callback
	));

	this->hexusOpponentItems->push_back(HexusOpponentItem::create(
		"Blink Godmode II",
		Resources::Maps_Platformer_Tutorials_TutorialExactValueScan1_TutorialExactValueScan1,
		index++,
		callback
	));
}

void HexusPuzzlesMenu::onMouseOver(HexusOpponentItem* tutorialItem)
{
	if (this->description->getString() != tutorialItem->tutorialDescription)
	{
		this->description->setString(tutorialItem->tutorialDescription);
	}
}

void HexusPuzzlesMenu::initializeListeners()
{
	this->getEventDispatcher()->removeEventListenersForTarget(this);

	EventListenerKeyboard* keyboardListener = EventListenerKeyboard::create();

	keyboardListener->onKeyPressed = CC_CALLBACK_2(HexusPuzzlesMenu::onKeyPressed, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}

void HexusPuzzlesMenu::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_ESCAPE:
		event->stopPropagation();
		NavigationEvents::navigateBack();
		break;
	}
}

void HexusPuzzlesMenu::onCloseClick(MenuSprite* menuSprite)
{
	NavigationEvents::navigateBack();
}
