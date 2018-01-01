#include "TutorialScreen.h"

TutorialScreen * TutorialScreen::create()
{
	TutorialScreen* tutorialScreen = new TutorialScreen();

	tutorialScreen->autorelease();

	return tutorialScreen;
}

TutorialScreen::TutorialScreen()
{
	this->currentPage = 0;

	this->tutorialWindow = Sprite::create(Resources::Menus_TutorialMenu_TutorialSelect);
	this->descriptionBox = Sprite::create(Resources::Menus_TutorialMenu_TutorialItem);
	this->description = Label::create("", Resources::Fonts_Montserrat_Medium, 14);
	this->closeButton = MenuSprite::create(Resources::Menus_Buttons_CloseButton, Resources::Menus_Buttons_CloseButtonHover, Resources::Menus_Buttons_CloseButtonClick);

	this->floatingBox1 = FloatingSprite::create(Resources::Menus_TutorialMenu_ObjectBox1, Vec2(-32.0f, -32.0f), Vec2(8.0f, 5.0f));
	this->floatingBox2 = FloatingSprite::create(Resources::Menus_TutorialMenu_ObjectBox2, Vec2(32.0f, 32.0f), Vec2(8.0f, 8.0f));
	this->floatingBox3 = FloatingSprite::create(Resources::Menus_TutorialMenu_ObjectBox3, Vec2(32.0f, 32.0f), Vec2(8.0f, 8.0f));
	this->floatingMisc1 = FloatingSprite::create(Resources::Menus_TutorialMenu_ObjectSci1, Vec2(64.0f, 32.0f), Vec2(7.0f, 8.0f));
	this->floatingMisc2 = FloatingSprite::create(Resources::Menus_TutorialMenu_ObjectSci2, Vec2(32.0f, 32.0f), Vec2(8.0f, 8.0f));
	this->floatingMisc3 = FloatingSprite::create(Resources::Menus_TutorialMenu_ObjectSci3, Vec2(-32.0f, 32.0f), Vec2(8.0f, 8.0f));
	this->floatingObelisk1 = FloatingSprite::create(Resources::Menus_TutorialMenu_ObjectObelisk1, Vec2(-64.0f, -64.0f), Vec2(8.0f, 8.0f));
	this->floatingObeliskParent = FloatingSprite::create(Resources::Menus_TutorialMenu_ObjectObeliskChildren, Vec2(-8.0f, 8.0f), Vec2(8.0f, 8.0f));
	this->floatingObeliskChild1 = FloatingSprite::create(Resources::Menus_TutorialMenu_ObjectObeliskChildren_01, Vec2(-16.0f, 16.0f), Vec2(8.0f, 8.0f));
	this->floatingObeliskChild2 = FloatingSprite::create(Resources::Menus_TutorialMenu_ObjectObeliskChildren_02, Vec2(16.0f, -16.0f), Vec2(8.0f, 8.0f));
	this->floatingObeliskChild3 = FloatingSprite::create(Resources::Menus_TutorialMenu_ObjectObeliskChildren_03, Vec2(16.0f, -16.0f), Vec2(8.0f, 8.0f));
	this->floatingObeliskChild4 = FloatingSprite::create(Resources::Menus_TutorialMenu_ObjectObeliskChildren_04, Vec2(-24.0f, 24.0f), Vec2(8.0f, 8.0f));
	this->floatingRocks2 = FloatingSprite::create(Resources::Menus_TutorialMenu_ObjectRocks2, Vec2(-32.0f, 32.0f), Vec2(8.0f, 8.0f));

	this->nether = ParticleSystemQuad::create(Resources::Particles_BlueNether);
	this->swirl = ParticleSystemQuad::create(Resources::Particles_BlueStarCircle);

	this->addChild(this->nether);
	this->addChild(this->swirl);

	this->addChild(this->floatingBox1);
	this->addChild(this->floatingBox2);
	this->addChild(this->floatingBox3);
	this->addChild(this->floatingMisc1);
	this->addChild(this->floatingMisc2);
	this->addChild(this->floatingMisc3);
	this->addChild(this->floatingObelisk1);
	this->addChild(this->floatingObeliskChild1);
	this->addChild(this->floatingObeliskChild3);
	this->addChild(this->floatingObeliskParent);
	this->addChild(this->floatingObeliskChild2);
	this->addChild(this->floatingObeliskChild4);
	this->addChild(this->floatingRocks2);

	this->addChild(this->tutorialWindow);
	this->addChild(this->closeButton);
	this->addChild(this->descriptionBox);
	this->addChild(this->description);

	this->loadLevels();
	this->closeButton->setClickCallback(CC_CALLBACK_1(TutorialScreen::onCloseClick, this));
	this->closeButton->setClickSound(Resources::Sounds_ClickBack1);

	for (std::vector<TutorialItem*>::iterator it = this->tutorialButtons->begin(); it != this->tutorialButtons->end(); ++it)
	{
		this->addChild(*it);
	}

	this->initializeListeners();
}

TutorialScreen::~TutorialScreen()
{
}

void TutorialScreen::onEnter()
{
	FadeScene::onEnter();

	float delay = 0.25f;
	float duration = 0.35f;

	Utils::fadeInObject(this->tutorialWindow, delay, duration);
	Utils::fadeInObject(this->descriptionBox, delay, duration);
	Utils::fadeInObject(this->description, delay, duration);
	Utils::fadeInObject(this->closeButton, delay, duration);

	for (std::vector<TutorialItem*>::iterator it = this->tutorialButtons->begin(); it != this->tutorialButtons->end(); ++it)
	{
		Utils::fadeInObject(*it, delay, duration);
	}

	// Initialize particles to an intermediate state
	Utils::accelerateParticles(this->swirl, 5.0f);
	Utils::accelerateParticles(this->nether, 1.0f);

	this->initializePositions();

	this->addChild(Mouse::claimInstance());
}

void TutorialScreen::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->nether->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->swirl->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));

	this->floatingBox1->setPosition(Vec2(origin.x + visibleSize.width / 2 + 640.0f, origin.y + visibleSize.height / 2 + 420.0f));
	this->floatingBox2->setPosition(Vec2(origin.x + visibleSize.width / 2 - 500.0f, origin.y + visibleSize.height / 2 + 64.0f));
	this->floatingBox3->setPosition(Vec2(origin.x + visibleSize.width / 2 - 640.0f, origin.y + visibleSize.height / 2 - 320.0f));
	this->floatingMisc1->setPosition(Vec2(origin.x + visibleSize.width / 2 + 224.0f, origin.y + visibleSize.height / 2 + 320.0f));
	this->floatingMisc2->setPosition(Vec2(origin.x + visibleSize.width / 2 + 540.0f, origin.y + visibleSize.height / 2));
	this->floatingMisc3->setPosition(Vec2(origin.x + visibleSize.width / 2 - 640.0f, origin.y + visibleSize.height / 2 + 420.0f));
	this->floatingObelisk1->setPosition(Vec2(origin.x + visibleSize.width / 2 - 196.0f, origin.y + visibleSize.height / 2 - 320.0f));
	this->floatingObeliskParent->setPosition(Vec2(origin.x + visibleSize.width / 2 - 240.0f, origin.y + visibleSize.height / 2 + 352.0f));
	this->floatingObeliskChild1->setPosition(Vec2(origin.x + visibleSize.width / 2 - 240.0f, origin.y + visibleSize.height / 2 + 352.0f));
	this->floatingObeliskChild2->setPosition(Vec2(origin.x + visibleSize.width / 2 - 240.0f, origin.y + visibleSize.height / 2 + 352.0f));
	this->floatingObeliskChild3->setPosition(Vec2(origin.x + visibleSize.width / 2 - 240.0f, origin.y + visibleSize.height / 2 + 352.0f));
	this->floatingObeliskChild4->setPosition(Vec2(origin.x + visibleSize.width / 2 - 240.0f, origin.y + visibleSize.height / 2 + 352.0f));
	this->floatingRocks2->setPosition(Vec2(origin.x + visibleSize.width / 2 + 240.0f, origin.y + visibleSize.height / 2 - 272.0f));

	this->tutorialWindow->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->closeButton->setPosition(Vec2(origin.x + visibleSize.width / 2 + 308.0f, origin.y + visibleSize.height / 2 + 222.0f));
	this->descriptionBox->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - 196.0f));
	this->description->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - 196.0f));

	for (std::vector<TutorialItem*>::iterator it = this->tutorialButtons->begin(); it != this->tutorialButtons->end(); ++it)
	{
		(*it)->initializePositions();
	}
}

void TutorialScreen::loadLevels()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto callback = CC_CALLBACK_1(TutorialScreen::onMouseOver, this);
	int index = 0;

	this->tutorialButtons = new std::vector<TutorialItem*>();

	this->tutorialButtons->push_back(TutorialItem::create(
		"Exact Value Scan I",
		Resources::Levels_TutorialExactScan1,
		index++,
		callback
	));

	this->tutorialButtons->push_back(TutorialItem::create(
		"Exact Value Scan II",
		Resources::Levels_TutorialExactScan1,
		index++,
		callback
	));

	this->tutorialButtons->push_back(TutorialItem::create(
		"Unknown Value Scan",
		Resources::Levels_Debug,
		index++,
		callback
	));

	this->tutorialButtons->push_back(TutorialItem::create(
		"Data Types - Float",
		Resources::Levels_Debug,
		index++,
		callback
	));

	this->tutorialButtons->push_back(TutorialItem::create(
		"Data Types - Double",
		Resources::Levels_Debug,
		index++,
		callback
	));

	this->tutorialButtons->push_back(TutorialItem::create(
		"Godmode",
		Resources::Levels_Debug,
		index++,
		callback
	));

	this->tutorialButtons->push_back(TutorialItem::create(
		"Position I",
		Resources::Levels_Debug,
		index++,
		callback
	));

	this->tutorialButtons->push_back(TutorialItem::create(
		"Position II",
		Resources::Levels_Debug,
		index++,
		callback
	));

	this->tutorialButtons->push_back(TutorialItem::create(
		"Blink Godmode I",
		Resources::Levels_Debug,
		index++,
		callback
	));

	this->tutorialButtons->push_back(TutorialItem::create(
		"Blink Godmode II",
		Resources::Levels_Debug,
		index++,
		callback
	));
}

void TutorialScreen::onMouseOver(TutorialItem* tutorialItem)
{
	if (this->description->getString() != tutorialItem->tutorialDescription)
	{
		this->description->setString(tutorialItem->tutorialDescription);
	}
}

void TutorialScreen::initializeListeners()
{
	EventListenerKeyboard* listener = EventListenerKeyboard::create();

	listener->onKeyPressed = CC_CALLBACK_2(TutorialScreen::onKeyPressed, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void TutorialScreen::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_ESCAPE:
		Director::getInstance()->popScene();
		break;
	}
}

void TutorialScreen::onCloseClick(MenuSprite* menuSprite)
{
	Director::getInstance()->popScene();
}
