#include "HexusChapterSelectMenu.h"

HexusChapterSelectMenu * HexusChapterSelectMenu::create()
{
	HexusChapterSelectMenu* instance = new HexusChapterSelectMenu();

	instance->autorelease();

	return instance;
}

HexusChapterSelectMenu::HexusChapterSelectMenu()
{
	this->chapters = new std::vector<HexusChapterPreview*>();
	this->scrollPane = ScrollPane::create(Size(1536.0f, 960.0f), Color4B(0, 0, 0, 196));
	this->nether = ParticleSystemQuad::create(Resources::Particles_BlueNether);
	this->swirl = ParticleSystemQuad::create(Resources::Particles_BlueStarCircle);
	this->hexusChapterPreviewJungle = HexusChapterPreviewJungle::create();
	this->hexusChapterPreviewRuins = HexusChapterPreviewRuins::create();
	this->hexusChapterPreviewForest = HexusChapterPreviewForest::create();
	this->hexusChapterPreviewCaverns = HexusChapterPreviewCaverns::create();
	this->hexusChapterPreviewCastle = HexusChapterPreviewCastle::create();
	this->hexusChapterPreviewIceCaps = HexusChapterPreviewIceCaps::create();
	this->hexusChapterPreviewVolcano = HexusChapterPreviewVolcano::create();
	this->hexusChapterPreviewObelisk = HexusChapterPreviewObelisk::create();
	this->hexusChapterPreviewMech = HexusChapterPreviewMech::create();

	this->scrollPane->setCascadeOpacityEnabled(true);

	auto callback = CC_CALLBACK_1(HexusChapterSelectMenu::onMouseOver, this);
	this->chapters->push_back(this->hexusChapterPreviewJungle);
	this->chapters->push_back(this->hexusChapterPreviewRuins);
	this->chapters->push_back(this->hexusChapterPreviewForest);
	this->chapters->push_back(this->hexusChapterPreviewCaverns);
	this->chapters->push_back(this->hexusChapterPreviewCastle);
	this->chapters->push_back(this->hexusChapterPreviewIceCaps);
	this->chapters->push_back(this->hexusChapterPreviewVolcano);
	this->chapters->push_back(this->hexusChapterPreviewObelisk);
	this->chapters->push_back(this->hexusChapterPreviewMech);

	for (std::vector<HexusChapterPreview*>::iterator it = this->chapters->begin(); it != this->chapters->end(); ++it)
	{
		this->scrollPane->addChild(*it);
	}

	this->addChild(this->nether);
	this->addChild(this->swirl);
	this->addChild(this->scrollPane);
	this->addChild(Mouse::create());
}

HexusChapterSelectMenu::~HexusChapterSelectMenu()
{
}

void HexusChapterSelectMenu::onEnter()
{
	FadeScene::onEnter();

	float delay = 0.25f;
	float duration = 0.35f;

	GameUtils::fadeInObject(this->scrollPane, delay, duration);

	for (std::vector<HexusChapterPreview*>::iterator it = this->chapters->begin(); it != this->chapters->end(); ++it)
	{
		GameUtils::fadeInObject(*it, delay, duration);
	}

	// Initialize particles to an intermediate state
	GameUtils::accelerateParticles(this->swirl, 5.0f);
	GameUtils::accelerateParticles(this->nether, 1.0f);
}

void HexusChapterSelectMenu::initializePositions()
{
	FadeScene::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->nether->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->swirl->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->scrollPane->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));

	Size scrollPaneSize = this->scrollPane->getPaneSize();

	int index = 0;

	for (std::vector<HexusChapterPreview*>::iterator it = this->chapters->begin(); it != this->chapters->end(); ++it)
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

void HexusChapterSelectMenu::initializeListeners()
{
	FadeScene::initializeListeners();

	EventListenerKeyboard* keyboardListener = EventListenerKeyboard::create();

	keyboardListener->onKeyPressed = CC_CALLBACK_2(HexusChapterSelectMenu::onKeyPressed, this);
	this->hexusChapterPreviewJungle->setClickCallback([]() { NavigationEvents::navigate(NavigationEvents::GameScreen::Minigames_Hexus_Chapter_Jungle); } );
	this->hexusChapterPreviewRuins->setClickCallback([]() { NavigationEvents::navigate(NavigationEvents::GameScreen::Minigames_Hexus_Chapter_Ruins); } );
	this->hexusChapterPreviewForest->setClickCallback([]() { NavigationEvents::navigate(NavigationEvents::GameScreen::Minigames_Hexus_Chapter_Forest); } );
	this->hexusChapterPreviewCaverns->setClickCallback([]() { NavigationEvents::navigate(NavigationEvents::GameScreen::Minigames_Hexus_Chapter_Caverns); } );
	this->hexusChapterPreviewCastle->setClickCallback([]() { NavigationEvents::navigate(NavigationEvents::GameScreen::Minigames_Hexus_Chapter_Castle); } );
	this->hexusChapterPreviewIceCaps->setClickCallback([]() { NavigationEvents::navigate(NavigationEvents::GameScreen::Minigames_Hexus_Chapter_IceCaps); } );
	this->hexusChapterPreviewVolcano->setClickCallback([]() { NavigationEvents::navigate(NavigationEvents::GameScreen::Minigames_Hexus_Chapter_Volcano); } );
	this->hexusChapterPreviewObelisk->setClickCallback([]() { NavigationEvents::navigate(NavigationEvents::GameScreen::Minigames_Hexus_Chapter_Obelisk); } );
	this->hexusChapterPreviewMech->setClickCallback([]() { NavigationEvents::navigate(NavigationEvents::GameScreen::Minigames_Hexus_Chapter_Mech); } );

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}

void HexusChapterSelectMenu::onMouseOver(HexusChapterPreview* HexusChapterPreview)
{
}

void HexusChapterSelectMenu::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
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

void HexusChapterSelectMenu::onCloseClick(MenuSprite* menuSprite)
{
	NavigationEvents::navigateBack();
}
