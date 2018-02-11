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
	this->ether = MenuSprite::create(Sprite::create(Resources::Menus_Backgrounds_Ether), Resources::Menus_Backgrounds_EtherSelected, Resources::Menus_Backgrounds_EtherSelected);
	this->etherParticles = ParticleGalaxy::create();
	this->eyes1 = Sprite::create();
	this->eyes2 = Sprite::create();
	this->foregroundVines = FloatingSprite::create(Resources::Menus_Backgrounds_Vines, Vec2(-24.0f, 0.0f), Vec2(7.0f, 5.0f));
	this->foregroundGrassBottom = FloatingSprite::create(Resources::Menus_Backgrounds_BottomSoil, Vec2(-32.0f, 0.0f), Vec2(7.0f, 5.0f));
	this->foregroundGrassTop = FloatingSprite::create(Resources::Menus_Backgrounds_TopLeaves, Vec2(-32.0f, 0.0f), Vec2(7.0f, 5.0f));
	this->foregroundLight = Sprite::create(Resources::Menus_Backgrounds_Light);
	this->slime = Sprite::create(Resources::Menus_TitleScreen_Slime_0000_SlimeFrames008);
	this->squallyNode = Node::create();
	this->squally = Sprite::create(Resources::Menus_TitleScreen_Squally);
	this->squallyWand = Sprite::create(Resources::Menus_TitleScreen_SquallyWand);

	this->createSlimeAnimation();

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

	const float floatSpeed = 3.0f;
	const float floatSpeedLarge = 6.0f;
	const float floatDeltaSmall = 64.0f;
	const float floatDeltaLarge = 344.0f;

	FiniteTimeAction* bounceX1 = EaseSineInOut::create(MoveBy::create(5.0f, Vec2(-8.0f, 0.0f)));
	FiniteTimeAction* bounceX2 = EaseSineInOut::create(MoveBy::create(5.0f, Vec2(8.0f, 0.0f)));
	FiniteTimeAction* bounceY1 = EaseSineInOut::create(MoveBy::create(floatSpeedLarge, Vec2(0.0f, -floatDeltaLarge)));
	FiniteTimeAction* bounceY2 = EaseSineInOut::create(MoveBy::create(floatSpeedLarge, Vec2(0.0f, floatDeltaLarge)));
	FiniteTimeAction* bounceY3 = EaseSineInOut::create(MoveBy::create(floatSpeed, Vec2(0.0f, -floatDeltaSmall)));
	FiniteTimeAction* bounceY4 = EaseSineInOut::create(MoveBy::create(floatSpeed, Vec2(0.0f, floatDeltaSmall)));

	// Prepare parameters to pass to lambdas
	Node* slimeNode = this->slime;
	Node* wandNode = this->squallyWand;
	Animation* slimeActionNode = this->slimeAnimation;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	this->slimeAnimation->retain();

	// Func to restore initial states to prevent floating point drift
	CallFunc* restoreState = CallFunc::create([wandNode] {
		wandNode->runAction(RotateTo::create(0.1f, 0.0f));
	});

	CallFunc* softRotateArm = CallFunc::create([wandNode] {
		wandNode->runAction(Sequence::create(RotateBy::create(5.0f, 8.0f), RotateBy::create(5.0f, -8.0f), nullptr));
	});

	CallFunc* rotateArm = CallFunc::create([wandNode] {
		wandNode->runAction(Sequence::create(RotateBy::create(0.1f, 15.0f), RotateBy::create(0.1f, -15.0f), nullptr));
	});

	CallFunc* pokeSlime = CallFunc::create([slimeNode, slimeActionNode] {
		slimeNode->runAction(Animate::create(slimeActionNode));
	});

	this->squallyNode->runAction(RepeatForever::create(
		Sequence::create(
			bounceX1,
			bounceX2,
			nullptr
		))
	);

	this->squallyNode->runAction(RepeatForever::create(
		Sequence::create(
			restoreState,
			softRotateArm,
			bounceY3,
			bounceY4,
			bounceY3,
			bounceY4,
			bounceY1,
			rotateArm,
			pokeSlime,
			bounceY4,
			bounceY3,
			rotateArm,
			pokeSlime,
			bounceY2,
			softRotateArm,
			bounceY3,
			bounceY4,
			bounceY3,
			bounceY4,
			nullptr
		))
	);

	this->hackerModeLabel = Label::create(HackerMode::getInstance()->getHackerModeAddressHex(), Resources::Fonts_Stormblade, 20);
	this->hackerModeLabel->setColor(Color3B(173, 135, 108));
	this->hackerModeLabel->setSkewX(-12.0f);

	this->squally->setFlipX(true);
	this->squallyWand->setFlipX(true);
	this->squallyNode->setScale(0.35f);
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

	this->squallyNode->addChild(this->squally);
	this->squallyNode->addChild(this->squallyWand);

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
	this->addChild(this->slime);
	this->addChild(this->squallyNode);

	this->initializeListeners();
}

TitleScreenBackground::~TitleScreenBackground()
{
}

void TitleScreenBackground::setMatrixClickCallback(std::function<void(MenuSprite*, EventMouse* args)> onMouseClick)
{
	this->ether->setClickCallback(onMouseClick);
}

void TitleScreenBackground::onEnter()
{
	Node::onEnter();

	// Initialize particles to an intermediate state
	Utils::accelerateParticles(this->fireflyParticles, 2.0f);
	Utils::accelerateParticles(this->windParticles, 5.0f);

	if (this->etherParticles->isVisible())
	{
		Utils::accelerateParticles(this->etherParticles, 5.0f);
	}
}

void TitleScreenBackground::initializeListeners()
{
	EventListenerCustom* customListener = EventListenerCustom::create(HackerMode::HackerModeEnabledEvent, CC_CALLBACK_1(TitleScreenBackground::onHackerModeEnabled, this));

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(customListener, this);

	// Add the hackermode node. This will allow for it's update method to run.
	this->addChild(HackerMode::getInstance());
}

void TitleScreenBackground::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->hackerModeLabel->setPosition(Vec2(visibleSize.width / 2 - 96.0f, visibleSize.height / 2 + 296.0f));

	this->background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->backgroundTrees->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->backgroundVines->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 320.0f));
	this->midgroundTrees->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->tree->setPosition(Vec2(visibleSize.width / 2 + 38.0f, visibleSize.height / 2 + 180.0f));
	this->ether->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - this->ether->getContentSize().height + 372.0f));
	this->etherParticles->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - this->ether->getContentSize().height + 372.0f));

	this->eyes1->setPosition(Vec2(visibleSize.width / 2 + 48.0f, visibleSize.height / 2 - 180.0f));
	this->eyes2->setPosition(Vec2(visibleSize.width / 2 + 48.0f, visibleSize.height / 2 - 180.0f));
	this->fog->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 120.0f));
	this->foregroundFog->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 256.0f));
	this->foregroundVines->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 196.0f));
	this->foregroundGrassBottom->setPosition(Vec2(visibleSize.width / 2, 0.0f));
	this->foregroundGrassTop->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 32.0f));
	this->foregroundLight->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - foregroundLight->getContentSize().height / 2));
	this->windParticles->setPosition(Vec2(visibleSize.width, visibleSize.height / 2));
	this->fireflyParticles->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->slime->setPosition(Vec2(visibleSize.width / 2 + 112.0f, visibleSize.height / 2 - 320.0f));
	this->squallyNode->setPosition(Vec2(visibleSize.width / 2 + 240.0f, visibleSize.height / 2 + 96.0f));
}

void TitleScreenBackground::onHackerModeEnabled(EventCustom* args)
{
	this->ether->setVisible(true);
	this->ether->runAction(FadeIn::create(1.0f));
	this->etherParticles->setVisible(true);
	this->etherParticles->runAction(FadeIn::create(2.0f));
	this->etherParticles->start();
}

void TitleScreenBackground::createSlimeAnimation()
{
	this->slimeAnimation = Animation::create();
	this->slimeAnimation->setDelayPerUnit(0.035f);

	this->slimeAnimation->addSpriteFrameWithFileName(Resources::Menus_TitleScreen_Slime_0000_SlimeFrames008);
	this->slimeAnimation->addSpriteFrameWithFileName(Resources::Menus_TitleScreen_Slime_0001_SlimeFrames009);
	this->slimeAnimation->addSpriteFrameWithFileName(Resources::Menus_TitleScreen_Slime_0002_SlimeFrames010);
	this->slimeAnimation->addSpriteFrameWithFileName(Resources::Menus_TitleScreen_Slime_0003_SlimeFrames011);
	this->slimeAnimation->addSpriteFrameWithFileName(Resources::Menus_TitleScreen_Slime_0004_SlimeFrames012);
	this->slimeAnimation->addSpriteFrameWithFileName(Resources::Menus_TitleScreen_Slime_0005_SlimeFrames013);
	this->slimeAnimation->addSpriteFrameWithFileName(Resources::Menus_TitleScreen_Slime_0006_SlimeFrames014);
	this->slimeAnimation->addSpriteFrameWithFileName(Resources::Menus_TitleScreen_Slime_0007_SlimeFrames015);
	this->slimeAnimation->addSpriteFrameWithFileName(Resources::Menus_TitleScreen_Slime_0008_SlimeFrames016);
	this->slimeAnimation->addSpriteFrameWithFileName(Resources::Menus_TitleScreen_Slime_0009_SlimeFrames017);
	this->slimeAnimation->addSpriteFrameWithFileName(Resources::Menus_TitleScreen_Slime_0010_SlimeFrames018);
	this->slimeAnimation->addSpriteFrameWithFileName(Resources::Menus_TitleScreen_Slime_0011_SlimeFrames019);
	this->slimeAnimation->addSpriteFrameWithFileName(Resources::Menus_TitleScreen_Slime_0012_SlimeFrames020);
	this->slimeAnimation->addSpriteFrameWithFileName(Resources::Menus_TitleScreen_Slime_0013_SlimeFrames021);
	this->slimeAnimation->addSpriteFrameWithFileName(Resources::Menus_TitleScreen_Slime_0014_SlimeFrames022);
	this->slimeAnimation->addSpriteFrameWithFileName(Resources::Menus_TitleScreen_Slime_0015_SlimeFrames023);
	this->slimeAnimation->addSpriteFrameWithFileName(Resources::Menus_TitleScreen_Slime_0016_SlimeFrames024);
	this->slimeAnimation->addSpriteFrameWithFileName(Resources::Menus_TitleScreen_Slime_0017_SlimeFrames025);
	this->slimeAnimation->addSpriteFrameWithFileName(Resources::Menus_TitleScreen_Slime_0018_SlimeFrames026);
	this->slimeAnimation->addSpriteFrameWithFileName(Resources::Menus_TitleScreen_Slime_0019_SlimeFrames027);
	this->slimeAnimation->addSpriteFrameWithFileName(Resources::Menus_TitleScreen_Slime_0020_SlimeFrames028);
	this->slimeAnimation->addSpriteFrameWithFileName(Resources::Menus_TitleScreen_Slime_0021_SlimeFrames029);
	this->slimeAnimation->addSpriteFrameWithFileName(Resources::Menus_TitleScreen_Slime_0022_SlimeFrames030);
	this->slimeAnimation->addSpriteFrameWithFileName(Resources::Menus_TitleScreen_Slime_0023_SlimeFrames031);
	this->slimeAnimation->addSpriteFrameWithFileName(Resources::Menus_TitleScreen_Slime_0024_SlimeFrames032);
	this->slimeAnimation->addSpriteFrameWithFileName(Resources::Menus_TitleScreen_Slime_0025_SlimeFrames033);
	this->slimeAnimation->addSpriteFrameWithFileName(Resources::Menus_TitleScreen_Slime_0026_SlimeFrames034);
	this->slimeAnimation->addSpriteFrameWithFileName(Resources::Menus_TitleScreen_Slime_0027_SlimeFrames035);
	this->slimeAnimation->addSpriteFrameWithFileName(Resources::Menus_TitleScreen_Slime_0028_SlimeFrames036);
	this->slimeAnimation->addSpriteFrameWithFileName(Resources::Menus_TitleScreen_Slime_0029_SlimeFrames037);
	this->slimeAnimation->addSpriteFrameWithFileName(Resources::Menus_TitleScreen_Slime_0030_SlimeFrames038);
	this->slimeAnimation->addSpriteFrameWithFileName(Resources::Menus_TitleScreen_Slime_0031_SlimeFrames039);
	this->slimeAnimation->addSpriteFrameWithFileName(Resources::Menus_TitleScreen_Slime_0032_SlimeFrames040);
	this->slimeAnimation->addSpriteFrameWithFileName(Resources::Menus_TitleScreen_Slime_0033_SlimeFrames041);
	this->slimeAnimation->addSpriteFrameWithFileName(Resources::Menus_TitleScreen_Slime_0034_SlimeFrames042);
	this->slimeAnimation->addSpriteFrameWithFileName(Resources::Menus_TitleScreen_Slime_0035_SlimeFrames043);
	this->slimeAnimation->addSpriteFrameWithFileName(Resources::Menus_TitleScreen_Slime_0036_SlimeFrames044);
	this->slimeAnimation->addSpriteFrameWithFileName(Resources::Menus_TitleScreen_Slime_0037_SlimeFrames045);
}
