#include "HexusMenu.h"

HexusMenu * HexusMenu::create()
{
	HexusMenu* instance = new HexusMenu();

	instance->autorelease();

	return instance;
}

HexusMenu::HexusMenu()
{
	this->hexusOpponents = new std::vector<HexusOpponentFrame*>();
	this->scrollPane = ScrollPane::create(Size(1536.0f, 960.0f), Color4B(0, 0, 0, 196));
	this->nether = ParticleSystemQuad::create(Resources::Particles_BlueNether);
	this->swirl = ParticleSystemQuad::create(Resources::Particles_BlueStarCircle);

	this->loadOpponents();

	for (std::vector<HexusOpponentFrame*>::iterator it = this->hexusOpponents->begin(); it != this->hexusOpponents->end(); ++it)
	{
		this->scrollPane->addChild(*it);
	}

	this->addChild(this->nether);
	this->addChild(this->swirl);
	this->addChild(this->scrollPane);
	this->addChild(Mouse::create());
}

HexusMenu::~HexusMenu()
{
}

void HexusMenu::onEnter()
{
	FadeScene::onEnter();

	float delay = 0.25f;
	float duration = 0.35f;

	GameUtils::fadeInObject(this->scrollPane, delay, duration);

	// Initialize particles to an intermediate state
	GameUtils::accelerateParticles(this->swirl, 5.0f);
	GameUtils::accelerateParticles(this->nether, 1.0f);
}

void HexusMenu::initializePositions()
{
	FadeScene::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->nether->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->swirl->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->scrollPane->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));

	Size scrollPaneSize = this->scrollPane->getPaneSize();

	int index = 0;

	for (std::vector<HexusOpponentFrame*>::iterator it = this->hexusOpponents->begin(); it != this->hexusOpponents->end(); ++it)
	{
		int x = index % 3;
		int y = index / 3;

		if (x == 0)
		{
			(*it)->setPositionX(scrollPaneSize.width / 2.0f - 496.0f);
		}
		else if (x == 1)
		{
			(*it)->setPositionX(scrollPaneSize.width / 2.0f);
		}
		else if (x == 2)
		{
			(*it)->setPositionX(scrollPaneSize.width / 2.0f + 496.0f);
		}

		(*it)->setPositionY(y * 680.0f + 480.0f);

		index++;
	}

	this->scrollPane->fitSizeToContent();
}

void HexusMenu::initializeListeners()
{
	FadeScene::initializeListeners();

	EventListenerKeyboard* keyboardListener = EventListenerKeyboard::create();

	keyboardListener->onKeyPressed = CC_CALLBACK_2(HexusMenu::onKeyPressed, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}

void HexusMenu::loadOpponents()
{
	auto callback = CC_CALLBACK_1(HexusMenu::onMouseOver, this);

	this->hexusOpponents->push_back(HexusOpponentFrame::create(HexusOpponentDataSanta::getInstance(), callback));
	this->hexusOpponents->push_back(HexusOpponentFrame::create(HexusOpponentDataSanta::getInstance(), callback));
	this->hexusOpponents->push_back(HexusOpponentFrame::create(HexusOpponentDataSanta::getInstance(), callback));
	this->hexusOpponents->push_back(HexusOpponentFrame::create(HexusOpponentDataSanta::getInstance(), callback));
	this->hexusOpponents->push_back(HexusOpponentFrame::create(HexusOpponentDataSanta::getInstance(), callback));
	this->hexusOpponents->push_back(HexusOpponentFrame::create(HexusOpponentDataSanta::getInstance(), callback));
	this->hexusOpponents->push_back(HexusOpponentFrame::create(HexusOpponentDataSanta::getInstance(), callback));
	this->hexusOpponents->push_back(HexusOpponentFrame::create(HexusOpponentDataSanta::getInstance(), callback));
	this->hexusOpponents->push_back(HexusOpponentFrame::create(HexusOpponentDataSanta::getInstance(), callback));
	this->hexusOpponents->push_back(HexusOpponentFrame::create(HexusOpponentDataSanta::getInstance(), callback));
	this->hexusOpponents->push_back(HexusOpponentFrame::create(HexusOpponentDataSanta::getInstance(), callback));
	this->hexusOpponents->push_back(HexusOpponentFrame::create(HexusOpponentDataSanta::getInstance(), callback));
	this->hexusOpponents->push_back(HexusOpponentFrame::create(HexusOpponentDataSanta::getInstance(), callback));
	this->hexusOpponents->push_back(HexusOpponentFrame::create(HexusOpponentDataSanta::getInstance(), callback));
	this->hexusOpponents->push_back(HexusOpponentFrame::create(HexusOpponentDataSanta::getInstance(), callback));
	this->hexusOpponents->push_back(HexusOpponentFrame::create(HexusOpponentDataSanta::getInstance(), callback));
}

void HexusMenu::onMouseOver(HexusOpponentFrame* hexusOpponentFrame)
{
}

void HexusMenu::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode)
	{
		case EventKeyboard::KeyCode::KEY_ESCAPE:
			event->stopPropagation();
			NavigationEvents::navigateBack();
			break;
		default:
			break;
	}
}

void HexusMenu::onCloseClick(MenuSprite* menuSprite)
{
	NavigationEvents::navigateBack();
}
