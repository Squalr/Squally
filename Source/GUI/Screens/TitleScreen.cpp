#include "TitleScreen.h"

int TitleScreen::hackerMode = 1;

TitleScreen * TitleScreen::create()
{
	TitleScreen* titleScreen = new TitleScreen();

	titleScreen->autorelease();

	return titleScreen;
}

TitleScreen::TitleScreen()
{
	SimpleAudioEngine* audio = SimpleAudioEngine::getInstance();

	if (!audio->isBackgroundMusicPlaying())
	{
		audio->preloadBackgroundMusic(Resources::Music_Will_we_get_there_Together.c_str());
		audio->playBackgroundMusic(Resources::Music_Will_we_get_there_Together.c_str(), true);
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->eyes1Anim = Animation::create();
	this->eyes2Anim = Animation::create();

	this->background = Sprite::create(Resources::Menus_TitleScreen_TitleScreen);
	this->fog = InfiniteParallaxNode::create(Resources::Menus_TitleScreen_bg_fog);
	this->foregroundFog = InfiniteParallaxNode::create(Resources::Menus_TitleScreen_bg_fog);
	this->backgroundVines = FloatingSprite::create(Resources::Menus_TitleScreen_bg_far1, Vec2(64.0f, -8.0f), Vec2(7.0f, 5.0f));
	this->backgroundTrees = FloatingSprite::create(Resources::Menus_TitleScreen_bg_back, Vec2(-48.0f, 8.0f), Vec2(7.0f, 5.0f));
	this->midgroundTrees = FloatingSprite::create(Resources::Menus_TitleScreen_bg_mid, Vec2(8.0f, -8.0f), Vec2(7.0f, 5.0f));
	this->tree = Sprite::create(Resources::Menus_TitleScreen_tree_fat);
	this->eyes1 = Sprite::create();
	this->eyes2 = Sprite::create();
	this->foregroundVines = FloatingSprite::create(Resources::Menus_TitleScreen_bg_top_lines, Vec2(-24.0f, 0.0f), Vec2(7.0f, 5.0f));
	this->foregroundGrassBottom = FloatingSprite::create(Resources::Menus_TitleScreen_bg_bott, Vec2(-32.0f, 0.0f), Vec2(7.0f, 5.0f));
	this->foregroundGrassTop = FloatingSprite::create(Resources::Menus_TitleScreen_bg_top, Vec2(-32.0f, 0.0f), Vec2(7.0f, 5.0f));
	this->foregroundLight = Sprite::create(Resources::Menus_TitleScreen_bg_light_02);
	this->squally = FloatingSprite::create(Resources::Menus_TitleScreen_Squally, Vec2(8.0f, 64.0f), Vec2(3.5f, 8.0f));

	this->titleBar = Sprite::create(Resources::Menus_TitleScreen_TitleBar);

	this->squally->setFlippedY(true);

	this->matrix = MenuSprite::create(Resources::Menus_TitleScreen_Monitor, Resources::Menus_TitleScreen_MonitorSelected, Resources::Menus_TitleScreen_MonitorSelected);
	this->storyModeButton = MenuSprite::create(Resources::Menus_TitleScreen_StoryModeButton, Resources::Menus_TitleScreen_StoryModeButtonHover, Resources::Menus_TitleScreen_StoryModeButtonClick);
	this->optionsButton = MenuSprite::create(Resources::Menus_TitleScreen_OptionsButton, Resources::Menus_TitleScreen_OptionsButtonHover, Resources::Menus_TitleScreen_OptionsButtonClick);
	this->exitButton = MenuSprite::create(Resources::Menus_TitleScreen_ExitButton, Resources::Menus_TitleScreen_ExitButtonHover, Resources::Menus_TitleScreen_ExitButtonClick);

	this->matrixParticles = ParticleGalaxy::create();
	this->windParticles = ParticleSystemQuad::create(Resources::Particles_Wind);
	this->fireflyParticles = ParticleSystemQuad::create(Resources::Particles_Fireflies2);

	this->matrix->SetClickCallback(CC_CALLBACK_1(TitleScreen::OnMenuClick, this));
	this->storyModeButton->SetClickCallback(CC_CALLBACK_1(TitleScreen::OnMenuClick, this));
	this->optionsButton->SetClickCallback(CC_CALLBACK_1(TitleScreen::OnMenuClick, this));
	this->exitButton->SetClickCallback(CC_CALLBACK_1(TitleScreen::OnMenuClick, this));

	this->eyes1Anim->addSpriteFrameWithFileName(Resources::Menus_TitleScreen_EyesA1);
	this->eyes1Anim->addSpriteFrameWithFileName(Resources::Menus_TitleScreen_EyesA2);
	this->eyes1Anim->addSpriteFrameWithFileName(Resources::Menus_TitleScreen_EyesA3);
	this->eyes1Anim->addSpriteFrameWithFileName(Resources::Menus_TitleScreen_EyesA4);
	this->eyes1Anim->addSpriteFrameWithFileName(Resources::Menus_TitleScreen_EyesA5);

	this->eyes2Anim->addSpriteFrameWithFileName(Resources::Menus_TitleScreen_EyesB1);
	this->eyes2Anim->addSpriteFrameWithFileName(Resources::Menus_TitleScreen_EyesB2);
	this->eyes2Anim->addSpriteFrameWithFileName(Resources::Menus_TitleScreen_EyesB3);
	this->eyes2Anim->addSpriteFrameWithFileName(Resources::Menus_TitleScreen_EyesB4);

	std::stringstream stream;
	stream << std::hex << (int)(&this->hackerMode);
	std::string hackerModeAddress = stream.str();
	std::transform(hackerModeAddress.begin(), hackerModeAddress.end(), hackerModeAddress.begin(), ::toupper);

	this->hackerModeLabel = Label::create(hackerModeAddress, Resources::Fonts_Stormblade, 16);
	this->hackerModeLabel->setColor(Color3B(173, 135, 108));
	this->hackerModeLabel->setSkewX(-12.0f);

	this->mouse = Mouse::create();
	this->clickableMenus = new vector<MenuSprite*>();

	this->hackerModeLabel->setPosition(Vec2(origin.x + visibleSize.width / 2 - 96.0f, origin.x + visibleSize.height / 2 + 296.0f));

	this->matrix->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - this->matrix->getContentSize().height + 372.0f));
	this->matrixParticles->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - this->matrix->getContentSize().height + 372.0f));
	this->background->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->backgroundVines->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - 196.0f));
	this->backgroundTrees->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->midgroundTrees->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->tree->setPosition(Vec2(origin.x + visibleSize.width / 2 + 38.0f, origin.y + visibleSize.height / 2 + 180.0f));
	this->eyes1->setPosition(Vec2(origin.x + visibleSize.width / 2 + 48.0f, origin.y + visibleSize.height / 2 - 180.0f));
	this->eyes2->setPosition(Vec2(origin.x + visibleSize.width / 2 + 48.0f, origin.y + visibleSize.height / 2 - 180.0f));
	this->fog->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - 120.0f));
	this->foregroundFog->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - 256.0f));
	this->foregroundVines->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - 196.0f));
	this->foregroundGrassBottom->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y));
	this->foregroundGrassTop->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - 32.0f));
	this->foregroundLight->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - foregroundLight->getContentSize().height / 2));
	this->windParticles->setPosition(Vec2(origin.x + visibleSize.width, origin.y + visibleSize.height / 2));
	this->fireflyParticles->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->squally->setPosition(Vec2(origin.x + visibleSize.width / 2 + 240.0f, origin.y + visibleSize.height / 2 - 32.0f));

	this->squally->setFlippedX(true);
	this->fog->runAction(RepeatForever::create(MoveBy::create(2.0f, Vec2(-92.0f, 0))));
	this->foregroundFog->runAction(RepeatForever::create(MoveBy::create(2.0f, Vec2(-196.0f, 0))));
	this->eyes1Anim->setDelayPerUnit(0.025f);
	this->eyes2Anim->setDelayPerUnit(0.025f);
	this->eyes1->runAction(RepeatForever::create(Sequence::create(Animate::create(this->eyes1Anim), DelayTime::create(5.0f), Animate::create(this->eyes1Anim)->reverse(), DelayTime::create(1.0f), nullptr)));
	this->eyes2->runAction(RepeatForever::create(Sequence::create(Animate::create(this->eyes2Anim), DelayTime::create(4.0f), Animate::create(this->eyes2Anim)->reverse(), DelayTime::create(0.75f), nullptr)));

	this->titleBar->setPosition(Vec2(origin.x + visibleSize.width / 2 - visibleSize.width / 3, origin.y + visibleSize.height / 2));
	this->storyModeButton->setPosition(Vec2(origin.x + visibleSize.width / 2 - visibleSize.width / 3, origin.y + visibleSize.height / 2 + 192.0f));
	this->optionsButton->setPosition(Vec2(origin.x + visibleSize.width / 2 - visibleSize.width / 3, origin.y + visibleSize.height / 2 + 64.0f));
	this->exitButton->setPosition(Vec2(origin.x + visibleSize.width / 2 - visibleSize.width / 3, origin.y + visibleSize.height / 2 - 128.0f));

	this->clickableMenus->push_back(this->matrix);
	this->clickableMenus->push_back(this->storyModeButton);
	this->clickableMenus->push_back(this->optionsButton);
	this->clickableMenus->push_back(this->exitButton);

	this->addChild(this->background);
	this->addChild(this->backgroundVines);
	this->addChild(this->backgroundTrees);
	this->addChild(this->midgroundTrees);
	this->addChild(this->fog);
	this->addChild(this->foregroundVines);
	this->addChild(this->tree);
	this->addChild(this->eyes1);
	this->addChild(this->eyes2);
	this->addChild(this->hackerModeLabel);
	this->addChild(this->matrix);
	this->addChild(this->matrixParticles);
	this->addChild(this->fireflyParticles);
	this->addChild(this->windParticles);
	this->addChild(this->foregroundFog);
	this->addChild(this->foregroundGrassBottom);
	this->addChild(this->foregroundGrassTop);
	this->addChild(this->foregroundLight);
	this->addChild(this->squally);
	this->addChild(this->titleBar);
	this->addChild(this->storyModeButton);
	this->addChild(this->optionsButton);
	this->addChild(this->exitButton);
	this->addChild(this->mouse);

	this->matrixParticles->setCascadeOpacityEnabled(true);
	this->matrixParticles->setVisible(false);
	this->matrixParticles->stopSystem();
	this->matrixParticles->setOpacity(0);
	this->matrix->setCascadeOpacityEnabled(true);
	this->matrix->setVisible(false);
	this->matrix->setOpacity(0);

	this->scheduleUpdate();
}

TitleScreen::~TitleScreen()
{
	delete(this->clickableMenus);
}

void TitleScreen::onEnter()
{
	Scene::onEnter();

	this->InitializeListeners();
}

void TitleScreen::update(float dt)
{
	Scene::update(dt);

	if (this->hackerMode != 0 && !this->matrix->isVisible())
	{
		this->matrix->setVisible(true);
		this->matrix->runAction(FadeIn::create(1.0f));
		this->matrixParticles->setVisible(true);
		this->matrixParticles->runAction(FadeIn::create(2.0f));
		this->matrixParticles->start();
	}
}

void TitleScreen::OnMenuClick(MenuSprite* menuSprite)
{
	if (menuSprite == this->matrix)
	{
		Director::getInstance()->replaceScene(TutorialScreen::create());
	}
	else if (menuSprite == this->storyModeButton)
	{
		Director::getInstance()->replaceScene(StoryMap::create());
	}
	else if (menuSprite == this->optionsButton)
	{
		Director::getInstance()->replaceScene(OptionsMenu::create());
	}
	else if (menuSprite == this->exitButton)
	{
		CCDirector::getInstance()->end();
	}
}

void TitleScreen::InitializeListeners()
{
	EventListenerMouse* mouseListener = EventListenerMouse::create();

	mouseListener->onMouseMove = CC_CALLBACK_1(TitleScreen::OnMouseMove, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, this);
}

void TitleScreen::OnMouseMove(EventMouse* event)
{
	this->mouse->SetCanClick(false);

	for (std::vector<MenuSprite*>::iterator it = this->clickableMenus->begin(); it != this->clickableMenus->end(); ++it)
	{
		MenuSprite* menuSprite = *it;

		if (menuSprite->isVisible() && Utils::Intersects(menuSprite, Vec2(event->getCursorX(), event->getCursorY())))
		{
			this->mouse->SetCanClick(true);
			return;
		}
	}
}
