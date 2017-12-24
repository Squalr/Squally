#include "TitleScreenBackground.h"

TitleScreenBackground * TitleScreenBackground::create()
{
	TitleScreenBackground* titleScreenBackground = new TitleScreenBackground();

	titleScreenBackground->autorelease();

	return titleScreenBackground;
}

TitleScreenBackground::TitleScreenBackground()
{
	this->eyes1Anim = Animation::create();
	this->eyes2Anim = Animation::create();

	this->background = Sprite::create(Resources::Menus_Backgrounds_ForestBackground);
	this->fog = InfiniteParallaxNode::create(Resources::Menus_Backgrounds_Fog);
	this->foregroundFog = InfiniteParallaxNode::create(Resources::Menus_Backgrounds_Fog);
	this->backgroundTrees = FloatingSprite::create(Resources::Menus_Backgrounds_LightTrees, Vec2(-48.0f, 8.0f), Vec2(7.0f, 5.0f));
	this->backgroundVines = FloatingSprite::create(Resources::Menus_Backgrounds_FarVines, Vec2(64.0f, -8.0f), Vec2(7.0f, 5.0f));
	this->midgroundTrees = FloatingSprite::create(Resources::Menus_Backgrounds_MidgroundTrees, Vec2(8.0f, -8.0f), Vec2(7.0f, 5.0f));
	this->tree = Sprite::create(Resources::Menus_Backgrounds_Tree);
	this->ether = MenuSprite::create(Resources::Menus_Backgrounds_Ether, Resources::Menus_Backgrounds_EtherSelected, Resources::Menus_Backgrounds_EtherSelected);
	this->etherParticles = ParticleGalaxy::create();
	this->eyes1 = Sprite::create();
	this->eyes2 = Sprite::create();
	this->foregroundVines = FloatingSprite::create(Resources::Menus_Backgrounds_Vines, Vec2(-24.0f, 0.0f), Vec2(7.0f, 5.0f));
	this->foregroundGrassBottom = FloatingSprite::create(Resources::Menus_Backgrounds_BottomSoil, Vec2(-32.0f, 0.0f), Vec2(7.0f, 5.0f));
	this->foregroundGrassTop = FloatingSprite::create(Resources::Menus_Backgrounds_TopLeaves, Vec2(-32.0f, 0.0f), Vec2(7.0f, 5.0f));
	this->foregroundLight = Sprite::create(Resources::Menus_Backgrounds_Light);
	this->squally = FloatingSprite::create(Resources::Menus_Backgrounds_Squally, Vec2(8.0f, 64.0f), Vec2(3.5f, 8.0f));

	this->squally->setFlippedY(true);

	this->etherParticles = ParticleGalaxy::create();
	this->windParticles = ParticleSystemQuad::create(Resources::Particles_Wind);
	this->fireflyParticles = ParticleSystemQuad::create(Resources::Particles_Fireflies2);

	this->eyes1Anim->addSpriteFrameWithFileName(Resources::Menus_Backgrounds_EyesA1);
	this->eyes1Anim->addSpriteFrameWithFileName(Resources::Menus_Backgrounds_EyesA2);
	this->eyes1Anim->addSpriteFrameWithFileName(Resources::Menus_Backgrounds_EyesA3);
	this->eyes1Anim->addSpriteFrameWithFileName(Resources::Menus_Backgrounds_EyesA4);
	this->eyes1Anim->addSpriteFrameWithFileName(Resources::Menus_Backgrounds_EyesA5);

	this->eyes2Anim->addSpriteFrameWithFileName(Resources::Menus_Backgrounds_EyesB1);
	this->eyes2Anim->addSpriteFrameWithFileName(Resources::Menus_Backgrounds_EyesB2);
	this->eyes2Anim->addSpriteFrameWithFileName(Resources::Menus_Backgrounds_EyesB3);
	this->eyes2Anim->addSpriteFrameWithFileName(Resources::Menus_Backgrounds_EyesB4);

	this->hackerModeLabel = Label::create(HackerMode::GetInstance()->GetHackerModeAddressHex(), Resources::Fonts_Stormblade, 16);
	this->hackerModeLabel->setColor(Color3B(173, 135, 108));
	this->hackerModeLabel->setSkewX(-12.0f);

	this->squally->setFlippedX(true);
	this->fog->runAction(RepeatForever::create(MoveBy::create(2.0f, Vec2(-92.0f, 0))));
	this->foregroundFog->runAction(RepeatForever::create(MoveBy::create(2.0f, Vec2(-196.0f, 0))));
	this->eyes1Anim->setDelayPerUnit(0.025f);
	this->eyes2Anim->setDelayPerUnit(0.025f);
	this->eyes1->runAction(RepeatForever::create(Sequence::create(Animate::create(this->eyes1Anim)->reverse(), DelayTime::create(1.54f), Animate::create(this->eyes1Anim), DelayTime::create(2.5f), nullptr)));
	this->eyes2->runAction(RepeatForever::create(Sequence::create(Animate::create(this->eyes2Anim)->reverse(), DelayTime::create(1.25f), Animate::create(this->eyes2Anim), DelayTime::create(3.25f), nullptr)));

	this->ether->setVisible(false);
	this->etherParticles->setCascadeOpacityEnabled(true);
	this->etherParticles->setVisible(false);
	this->etherParticles->stopSystem();
	this->etherParticles->setOpacity(0);

	this->addChild(this->background);
	this->addChild(this->backgroundTrees);
	this->addChild(this->backgroundVines);
	this->addChild(this->midgroundTrees);
	this->addChild(this->fog);
	this->addChild(this->foregroundVines);
	this->addChild(this->tree);
	this->addChild(this->hackerModeLabel);
	this->addChild(this->ether);
	this->addChild(this->etherParticles);
	this->addChild(this->eyes1);
	this->addChild(this->eyes2);
	this->addChild(this->fireflyParticles);
	this->addChild(this->windParticles);
	this->addChild(this->foregroundFog);
	this->addChild(this->foregroundGrassBottom);
	this->addChild(this->foregroundGrassTop);
	this->addChild(this->foregroundLight);
	this->addChild(this->squally);

	this->InitializeListeners();
}

TitleScreenBackground::~TitleScreenBackground()
{
}

void TitleScreenBackground::SetMatrixClickCallback(std::function<void(MenuSprite*, EventMouse* args)> onMouseClick)
{
	this->ether->SetClickCallback(onMouseClick);
}

void TitleScreenBackground::onEnter()
{
	Node::onEnter();

	// Initialize particles to an intermediate state
	Utils::AccelerateParticles(this->fireflyParticles, 2.0f);
	Utils::AccelerateParticles(this->windParticles, 5.0f);

	if (this->etherParticles->isVisible())
	{
		Utils::AccelerateParticles(this->etherParticles, 5.0f);
	}
}

void TitleScreenBackground::InitializeListeners()
{
	EventListenerCustom* customListener = EventListenerCustom::create(HackerMode::GetInstance()->HackerModeEnabledEvent, CC_CALLBACK_1(TitleScreenBackground::OnHackerModeEnabled, this));

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(customListener, this);

	// Add the hackermode node. This will allow for it's update method to run.
	this->addChild(HackerMode::GetInstance());
}

void TitleScreenBackground::InitializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->hackerModeLabel->setPosition(Vec2(origin.x + visibleSize.width / 2 - 96.0f, origin.x + visibleSize.height / 2 + 296.0f));

	this->background->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->backgroundTrees->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->backgroundVines->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - 320.0f));
	this->midgroundTrees->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->tree->setPosition(Vec2(origin.x + visibleSize.width / 2 + 38.0f, origin.y + visibleSize.height / 2 + 180.0f));
	this->ether->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - this->ether->getContentSize().height + 372.0f));
	this->etherParticles->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - this->ether->getContentSize().height + 372.0f));

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
}

void TitleScreenBackground::OnHackerModeEnabled(EventCustom* args)
{
	this->ether->setVisible(true);
	this->ether->runAction(FadeIn::create(1.0f));
	this->etherParticles->setVisible(true);
	this->etherParticles->runAction(FadeIn::create(2.0f));
	this->etherParticles->start();
}
