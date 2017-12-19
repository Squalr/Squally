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
		// audio->playBackgroundMusic(Resources::Music_Will_we_get_there_Together.c_str(), true);
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->background = Sprite::create(Resources::Menus_TitleScreen_TitleScreen);
	this->fog = InfiniteParallaxNode::create(Resources::Menus_TitleScreen_bg_fog);
	this->foregroundFog = InfiniteParallaxNode::create(Resources::Menus_TitleScreen_bg_fog);
	this->backgroundVines = Sprite::create(Resources::Menus_TitleScreen_bg_far1);
	this->backgroundTrees = Sprite::create(Resources::Menus_TitleScreen_bg_back);
	this->midgroundTrees = Sprite::create(Resources::Menus_TitleScreen_bg_mid);
	this->tree = Sprite::create(Resources::Menus_TitleScreen_tree_fat);
	this->foregroundVines = Sprite::create(Resources::Menus_TitleScreen_bg_top_lines);
	this->foregroundGrassBottom = Sprite::create(Resources::Menus_TitleScreen_bg_bott);
	this->foregroundGrassTop = Sprite::create(Resources::Menus_TitleScreen_bg_top);
	this->foregroundLight = Sprite::create(Resources::Menus_TitleScreen_bg_light_02);

	this->squally = Sprite::create(Resources::Menus_TitleScreen_Squally);
	this->titleLabel = MenuLabel::create("Squally", Resources::Fonts_Marker_Felt, titleFontSize);
	this->titleBar = Sprite::create(Resources::Menus_TitleScreen_TitleBar);

	this->matrix = MenuSprite::create(Resources::Menus_TitleScreen_Monitor, Resources::Menus_TitleScreen_MonitorSelected, Resources::Menus_TitleScreen_MonitorSelected);
	this->storyModeButton = MenuSprite::create(Resources::Menus_TitleScreen_StoryModeButton, Resources::Menus_TitleScreen_StoryModeButtonHover, Resources::Menus_TitleScreen_StoryModeButtonClick);
	this->optionsButton = MenuSprite::create(Resources::Menus_TitleScreen_OptionsButton, Resources::Menus_TitleScreen_OptionsButtonHover, Resources::Menus_TitleScreen_OptionsButtonClick);
	this->exitButton = MenuSprite::create(Resources::Menus_TitleScreen_ExitButton, Resources::Menus_TitleScreen_ExitButtonHover, Resources::Menus_TitleScreen_ExitButtonClick);

	this->matrixParticles = ParticleGalaxy::create();
	this->foregroundParticles = ParticleSystem::create(Resources::Particles_title);
	this->foregroundParticles->setTexture(TextureCache::sharedTextureCache()->addImage(Resources::Ingame_Objects_Egg));
	foregroundParticles->resetSystem();

	this->matrix->SetClickCallback(CC_CALLBACK_1(TitleScreen::OnMenuClick, this));
	this->storyModeButton->SetClickCallback(CC_CALLBACK_1(TitleScreen::OnMenuClick, this));
	this->optionsButton->SetClickCallback(CC_CALLBACK_1(TitleScreen::OnMenuClick, this));
	this->exitButton->SetClickCallback(CC_CALLBACK_1(TitleScreen::OnMenuClick, this));

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
	this->titleLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - this->titleLabel->getContentSize().height + menuOffset - spacing * 1.5));
	this->background->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->backgroundVines->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - 196.0f));
	this->backgroundTrees->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->midgroundTrees->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->tree->setPosition(Vec2(origin.x + visibleSize.width / 2 + 38.0f, origin.y + visibleSize.height / 2 + 180.0f));
	this->fog->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - 120.0f));
	this->foregroundFog->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - 256.0f));
	this->foregroundVines->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - 196.0f));
	this->foregroundGrassBottom->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y));
	this->foregroundGrassTop->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - 32.0f));
	this->foregroundLight->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - foregroundLight->getContentSize().height / 2));
	this->foregroundParticles->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->squally->setPosition(Vec2(origin.x + visibleSize.width / 2 + 240.0f, origin.y + visibleSize.height / 2 - 32.0f));
	this->squally->setFlippedX(true);

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
	this->addChild(this->hackerModeLabel);
	this->addChild(this->matrix);
	this->addChild(this->matrixParticles);
	this->addChild(this->foregroundFog);
	this->addChild(this->foregroundGrassBottom);
	this->addChild(this->foregroundGrassTop);
	this->addChild(this->foregroundLight);
	this->addChild(this->squally);
	this->addChild(this->foregroundParticles);
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
	this->InitializeMovement();
}

void TitleScreen::InitializeMovement()
{
	float squallyDistanceX = 8.0f;
	float squallyDistanceY = 64.0f;
	float squallySpeedX = 3.5f;
	float squallySpeedY = 8.0f;

	// Squally bounce
	FiniteTimeAction* bounceX1 = EaseSineInOut::create(MoveBy::create(squallySpeedX, Vec2(squallyDistanceX, 0.0f)));
	FiniteTimeAction* bounceX2 = EaseSineInOut::create(MoveBy::create(squallySpeedX, Vec2(-squallyDistanceX, 0.0f)));
	FiniteTimeAction* bounceY1 = EaseSineInOut::create(MoveBy::create(squallySpeedY, Vec2(0.0f, squallyDistanceY)));
	FiniteTimeAction* bounceY2 = EaseSineInOut::create(MoveBy::create(squallySpeedY, Vec2(0.0f, -squallyDistanceY)));

	this->squally->runAction(RepeatForever::create(Sequence::create(bounceX1, bounceX2, nullptr)));
	this->squally->runAction(RepeatForever::create(Sequence::create(bounceY1, bounceY2, nullptr)));

	// Fog parallax
	this->fog->runAction(RepeatForever::create(MoveBy::create(2.0f, Vec2(-92.0f, 0))));
	this->foregroundFog->runAction(RepeatForever::create(MoveBy::create(2.0f, Vec2(-196.0f, 0))));

	// Background shift
	float backgroundDistanceX01 = 64.0f;
	float backgroundDistanceX02 = -48.0f;
	float backgroundDistanceX03 = 32.0f;
	float backgroundDistanceX04 = -24.0f;
	float backgroundDistanceX05 = -32.0f;
	float backgroundDistanceX06 = -32.0f;

	float backgroundDistanceY01 = -8.0f;
	float backgroundDistanceY02 = 8.0f;
	float backgroundDistanceY03 = -8.0f;
	float backgroundDistanceY04 = 8.0f;
	float backgroundDistanceY05 = -8.0f;
	float backgroundDistanceY06 = 8.0f;

	float backgroundSpeedX = 7.0f;
	float backgroundSpeedY = 5.0f;

	FiniteTimeAction* shiftLeft01 = EaseSineInOut::create(MoveBy::create(backgroundSpeedX, Vec2(backgroundDistanceX01, 0.0f)));
	FiniteTimeAction* shiftRight01 = EaseSineInOut::create(MoveBy::create(backgroundSpeedX, Vec2(-backgroundDistanceX01, 0.0f)));
	FiniteTimeAction* shiftUp01 = EaseSineInOut::create(MoveBy::create(backgroundSpeedY, Vec2(0.0f, backgroundDistanceY01)));
	FiniteTimeAction* shiftDown01 = EaseSineInOut::create(MoveBy::create(backgroundSpeedY, Vec2(0.0f, -backgroundDistanceY01)));

	FiniteTimeAction* shiftLeft02 = EaseSineInOut::create(MoveBy::create(backgroundSpeedX, Vec2(backgroundDistanceX02, 0.0f)));
	FiniteTimeAction* shiftRight02 = EaseSineInOut::create(MoveBy::create(backgroundSpeedX, Vec2(-backgroundDistanceX02, 0.0f)));
	FiniteTimeAction* shiftUp02 = EaseSineInOut::create(MoveBy::create(backgroundSpeedY, Vec2(0.0f, backgroundDistanceY02)));
	FiniteTimeAction* shiftDown02 = EaseSineInOut::create(MoveBy::create(backgroundSpeedY, Vec2(0.0f, -backgroundDistanceY02)));

	FiniteTimeAction* shiftLeft03 = EaseSineInOut::create(MoveBy::create(backgroundSpeedX, Vec2(backgroundDistanceX03, 0.0f)));
	FiniteTimeAction* shiftRight03 = EaseSineInOut::create(MoveBy::create(backgroundSpeedX, Vec2(-backgroundDistanceX03, 0.0f)));
	FiniteTimeAction* shiftUp03 = EaseSineInOut::create(MoveBy::create(backgroundSpeedY, Vec2(0.0f, backgroundDistanceY03)));
	FiniteTimeAction* shiftDown03 = EaseSineInOut::create(MoveBy::create(backgroundSpeedY, Vec2(0.0f, -backgroundDistanceY03)));

	FiniteTimeAction* shiftLeft04 = EaseSineInOut::create(MoveBy::create(backgroundSpeedX, Vec2(backgroundDistanceX04, 0.0f)));
	FiniteTimeAction* shiftRight04 = EaseSineInOut::create(MoveBy::create(backgroundSpeedX, Vec2(-backgroundDistanceX04, 0.0f)));
	FiniteTimeAction* shiftUp04 = EaseSineInOut::create(MoveBy::create(backgroundSpeedY, Vec2(0.0f, backgroundDistanceY04)));
	FiniteTimeAction* shiftDown04 = EaseSineInOut::create(MoveBy::create(backgroundSpeedY, Vec2(0.0f, -backgroundDistanceY04)));

	FiniteTimeAction* shiftLeft05 = EaseSineInOut::create(MoveBy::create(backgroundSpeedX, Vec2(backgroundDistanceX05, 0.0f)));
	FiniteTimeAction* shiftRight05 = EaseSineInOut::create(MoveBy::create(backgroundSpeedX, Vec2(-backgroundDistanceX05, 0.0f)));
	FiniteTimeAction* shiftUp05 = EaseSineInOut::create(MoveBy::create(backgroundSpeedY, Vec2(0.0f, backgroundDistanceY05)));
	FiniteTimeAction* shiftDown05 = EaseSineInOut::create(MoveBy::create(backgroundSpeedY, Vec2(0.0f, -backgroundDistanceY05)));

	FiniteTimeAction* shiftLeft06 = EaseSineInOut::create(MoveBy::create(backgroundSpeedX, Vec2(backgroundDistanceX06, 0.0f)));
	FiniteTimeAction* shiftRight06 = EaseSineInOut::create(MoveBy::create(backgroundSpeedX, Vec2(-backgroundDistanceX06, 0.0f)));
	FiniteTimeAction* shiftUp06 = EaseSineInOut::create(MoveBy::create(backgroundSpeedY, Vec2(0.0f, backgroundDistanceY06)));
	FiniteTimeAction* shiftDown06 = EaseSineInOut::create(MoveBy::create(backgroundSpeedY, Vec2(0.0f, -backgroundDistanceY06)));

	this->backgroundVines->runAction(RepeatForever::create(Sequence::create(shiftLeft01, shiftRight01, nullptr)));
	this->backgroundVines->runAction(RepeatForever::create(Sequence::create(shiftUp01, shiftDown01, nullptr)));
	this->backgroundTrees->runAction(RepeatForever::create(Sequence::create(shiftLeft02, shiftRight02, nullptr)));
	this->backgroundTrees->runAction(RepeatForever::create(Sequence::create(shiftUp02, shiftDown02, nullptr)));
	this->midgroundTrees->runAction(RepeatForever::create(Sequence::create(shiftLeft03, shiftRight03, nullptr)));
	this->midgroundTrees->runAction(RepeatForever::create(Sequence::create(shiftUp03, shiftDown03, nullptr)));
	this->foregroundVines->runAction(RepeatForever::create(Sequence::create(shiftLeft04, shiftRight04, nullptr)));
	this->foregroundVines->runAction(RepeatForever::create(Sequence::create(shiftUp04, shiftDown04, nullptr)));
	this->foregroundGrassBottom->runAction(RepeatForever::create(Sequence::create(shiftLeft05, shiftRight05, nullptr)));
	//this->foregroundGrassBottom->runAction(RepeatForever::create(Sequence::create(shiftUp05, shiftDown05, nullptr)));
	this->foregroundGrassTop->runAction(RepeatForever::create(Sequence::create(shiftLeft06, shiftRight06, nullptr)));
	//this->foregroundGrassTop->runAction(RepeatForever::create(Sequence::create(shiftUp06, shiftDown06, nullptr)));
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
