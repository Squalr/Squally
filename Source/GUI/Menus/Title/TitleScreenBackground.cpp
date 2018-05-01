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
	this->eyes1 = Sprite::create();
	this->eyes2 = Sprite::create();
	this->foregroundVines = FloatingSprite::create(Resources::Menus_Backgrounds_Vines, Vec2(-24.0f, 0.0f), Vec2(7.0f, 5.0f));
	this->foregroundGrassBottom = FloatingSprite::create(Resources::Menus_Backgrounds_BottomSoil, Vec2(-32.0f, 0.0f), Vec2(7.0f, 5.0f));
	this->foregroundGrassTop = FloatingSprite::create(Resources::Menus_Backgrounds_TopLeaves, Vec2(-32.0f, 0.0f), Vec2(7.0f, 5.0f));
	this->foregroundLight = Sprite::create(Resources::Menus_Backgrounds_Light);
	this->slimeNode = Node::create();
	this->slime = Sprite::create(Resources::Menus_TitleScreen_Slime_Slime_0000_SlimeFrames008);
	this->squallyNode = Node::create();
	this->squally = AnimationNode::create(Resources::Entities_Player_Animations);

	this->squally->setScale(0.5f);

	this->squallyEntity = this->squally->play("Entity");
	this->squallyEntity->setCurrentAnimation("Title");

	this->createSlimeAnimation();

	this->windParticles = ParticleSystemQuad::create(Resources::Particles_Wind);
	this->fireflyParticles = ParticleSystemQuad::create(Resources::Particles_Fireflies2);

	this->eyes1Anim->addSpriteFrameWithFileName(Resources::Menus_Backgrounds_EyesA1);
	this->eyes1Anim->addSpriteFrameWithFileName(Resources::Menus_Backgrounds_EyesA2);
	this->eyes1Anim->addSpriteFrameWithFileName(Resources::Menus_Backgrounds_EyesA3);
	this->eyes1Anim->addSpriteFrameWithFileName(Resources::Menus_Backgrounds_EyesA4);
	this->eyes1Anim->addSpriteFrameWithFileName(Resources::Menus_Backgrounds_EyesA5);
	this->eyes1Anim->retain();

	this->eyes2Anim->addSpriteFrameWithFileName(Resources::Menus_Backgrounds_EyesB1);
	this->eyes2Anim->addSpriteFrameWithFileName(Resources::Menus_Backgrounds_EyesB2);
	this->eyes2Anim->addSpriteFrameWithFileName(Resources::Menus_Backgrounds_EyesB3);
	this->eyes2Anim->addSpriteFrameWithFileName(Resources::Menus_Backgrounds_EyesB4);
	this->eyes2Anim->retain();

	this->slimeNode->addChild(this->slime);
	this->squallyNode->addChild(this->squally);

	this->addChild(this->background);
	this->addChild(this->backgroundTrees);
	this->addChild(this->backgroundVines);
	this->addChild(this->midgroundTrees);
	this->addChild(this->fog);
	this->addChild(this->foregroundVines);
	this->addChild(this->tree);
	this->addChild(this->eyes1);
	this->addChild(this->eyes2);
	this->addChild(this->slimeNode);
	this->addChild(this->squallyNode);
	this->addChild(this->fireflyParticles);
	this->addChild(this->windParticles);
	this->addChild(this->foregroundFog);
	this->addChild(this->foregroundGrassBottom);
	this->addChild(this->foregroundGrassTop);
	this->addChild(this->foregroundLight);

	this->initializeListeners();
}

TitleScreenBackground::~TitleScreenBackground()
{
}

void TitleScreenBackground::onEnter()
{
	Node::onEnter();

	// Initialize particles to an intermediate state
	GameUtils::accelerateParticles(this->fireflyParticles, 2.0f);
	GameUtils::accelerateParticles(this->windParticles, 5.0f);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 base = Vec2(visibleSize.width / 2 + 228.0f, visibleSize.height / 2 + 160.0f);

	const float floatSpeed = 3.0f;
	const float floatSpeedPostSink = 1.25f;
	const float sinkSpeed = 6.0f;
	const float floatDelta = 64.0f;
	const float floatDeltaPostSink = 8.0f;
	const float sinkOffset = 420.0f;

	FiniteTimeAction* bounceDown = EaseSineInOut::create(MoveTo::create(floatSpeed, Vec2(base.x, base.y - floatDelta)));
	FiniteTimeAction* bounceUp = EaseSineInOut::create(MoveTo::create(floatSpeed, Vec2(base.x, base.y)));
	FiniteTimeAction* sinkDown = EaseSineInOut::create(MoveTo::create(sinkSpeed, Vec2(base.x, base.y - sinkOffset)));
	FiniteTimeAction* bounceUpPostSink = EaseSineInOut::create(MoveTo::create(floatSpeedPostSink, Vec2(base.x, base.y - sinkOffset + floatDeltaPostSink)));
	FiniteTimeAction* bounceDownPostSink = EaseSineInOut::create(MoveTo::create(floatSpeedPostSink, Vec2(base.x, base.y - sinkOffset)));
	FiniteTimeAction* sinkUp = EaseSineInOut::create(MoveTo::create(sinkSpeed, Vec2(base.x, base.y)));

	// Prepare parameters to pass to lambdas
	Node* slimeNodeLocal = this->slimeNode;
	Node* slimeSpriteLocal = this->slime;
	SpriterEngine::EntityInstance* squallyLocal = this->squallyEntity;
	Animation* slimeActionNode = this->slimeAnimation;
	this->slimeAnimation->retain();

	CallFunc* jiggleSlime = CallFunc::create([slimeSpriteLocal, slimeActionNode] {
		slimeSpriteLocal->runAction(Animate::create(slimeActionNode));
	});

	jiggleSlime->retain();

	CallFunc* pokeSlime = CallFunc::create([squallyLocal, jiggleSlime] {
		squallyLocal->setCurrentAnimation("TitlePoke");
		jiggleSlime->execute();
	});

	pokeSlime->retain();

	this->squallyNode->runAction(RepeatForever::create(
		Sequence::create(
			bounceDown,
			bounceUp,
			bounceDown,
			bounceUp,
			bounceDown,
			bounceUp,
			sinkDown,
			pokeSlime,
			bounceUpPostSink,
			bounceDownPostSink,
			pokeSlime,
			sinkUp,
			bounceDown,
			bounceUp,
			bounceDown,
			bounceUp,
			bounceDown,
			bounceUp,
			nullptr
		))
	);

	this->squally->setFlippedX(true);
	this->squallyNode->setScale(0.35f);
	this->fog->runAction(RepeatForever::create(MoveBy::create(2.0f, Vec2(-92.0f, 0))));
	this->foregroundFog->runAction(RepeatForever::create(MoveBy::create(2.0f, Vec2(-196.0f, 0))));
	this->eyes1Anim->setDelayPerUnit(0.025f);
	this->eyes2Anim->setDelayPerUnit(0.025f);
	this->eyes1->runAction(RepeatForever::create(Sequence::create(Animate::create(this->eyes1Anim)->reverse(), DelayTime::create(1.54f), Animate::create(this->eyes1Anim), DelayTime::create(2.5f), nullptr)));
	this->eyes2->runAction(RepeatForever::create(Sequence::create(Animate::create(this->eyes2Anim)->reverse(), DelayTime::create(1.25f), Animate::create(this->eyes2Anim), DelayTime::create(3.25f), nullptr)));

}

void TitleScreenBackground::initializeListeners()
{
}

void TitleScreenBackground::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->backgroundTrees->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->backgroundVines->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 320.0f));
	this->midgroundTrees->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->tree->setPosition(Vec2(visibleSize.width / 2 + 38.0f, visibleSize.height / 2 + 180.0f));

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
	this->slimeNode->setPosition(Vec2(visibleSize.width / 2 + 112.0f, visibleSize.height / 2 - 320.0f));
	this->squallyNode->setPosition(Vec2(visibleSize.width / 2 + 228.0f, visibleSize.height / 2 + 160.0f));
}

void TitleScreenBackground::createSlimeAnimation()
{
	this->slimeAnimation = Animation::create();
	this->slimeAnimation->setDelayPerUnit(0.035f);

	this->slimeAnimation->addSpriteFrameWithFileName(Resources::Menus_TitleScreen_Slime_Slime_0000_SlimeFrames008);
	this->slimeAnimation->addSpriteFrameWithFileName(Resources::Menus_TitleScreen_Slime_Slime_0001_SlimeFrames009);
	this->slimeAnimation->addSpriteFrameWithFileName(Resources::Menus_TitleScreen_Slime_Slime_0002_SlimeFrames010);
	this->slimeAnimation->addSpriteFrameWithFileName(Resources::Menus_TitleScreen_Slime_Slime_0003_SlimeFrames011);
	this->slimeAnimation->addSpriteFrameWithFileName(Resources::Menus_TitleScreen_Slime_Slime_0004_SlimeFrames012);
	this->slimeAnimation->addSpriteFrameWithFileName(Resources::Menus_TitleScreen_Slime_Slime_0005_SlimeFrames013);
	this->slimeAnimation->addSpriteFrameWithFileName(Resources::Menus_TitleScreen_Slime_Slime_0006_SlimeFrames014);
	this->slimeAnimation->addSpriteFrameWithFileName(Resources::Menus_TitleScreen_Slime_Slime_0007_SlimeFrames015);
	this->slimeAnimation->addSpriteFrameWithFileName(Resources::Menus_TitleScreen_Slime_Slime_0008_SlimeFrames016);
	this->slimeAnimation->addSpriteFrameWithFileName(Resources::Menus_TitleScreen_Slime_Slime_0009_SlimeFrames017);
	this->slimeAnimation->addSpriteFrameWithFileName(Resources::Menus_TitleScreen_Slime_Slime_0010_SlimeFrames018);
	this->slimeAnimation->addSpriteFrameWithFileName(Resources::Menus_TitleScreen_Slime_Slime_0011_SlimeFrames019);
	this->slimeAnimation->addSpriteFrameWithFileName(Resources::Menus_TitleScreen_Slime_Slime_0012_SlimeFrames020);
	this->slimeAnimation->addSpriteFrameWithFileName(Resources::Menus_TitleScreen_Slime_Slime_0013_SlimeFrames021);
	this->slimeAnimation->addSpriteFrameWithFileName(Resources::Menus_TitleScreen_Slime_Slime_0014_SlimeFrames022);
	this->slimeAnimation->addSpriteFrameWithFileName(Resources::Menus_TitleScreen_Slime_Slime_0015_SlimeFrames023);
	this->slimeAnimation->addSpriteFrameWithFileName(Resources::Menus_TitleScreen_Slime_Slime_0016_SlimeFrames024);
	this->slimeAnimation->addSpriteFrameWithFileName(Resources::Menus_TitleScreen_Slime_Slime_0017_SlimeFrames025);
	this->slimeAnimation->addSpriteFrameWithFileName(Resources::Menus_TitleScreen_Slime_Slime_0018_SlimeFrames026);
	this->slimeAnimation->addSpriteFrameWithFileName(Resources::Menus_TitleScreen_Slime_Slime_0019_SlimeFrames027);
	this->slimeAnimation->addSpriteFrameWithFileName(Resources::Menus_TitleScreen_Slime_Slime_0020_SlimeFrames028);
	this->slimeAnimation->addSpriteFrameWithFileName(Resources::Menus_TitleScreen_Slime_Slime_0021_SlimeFrames029);
	this->slimeAnimation->addSpriteFrameWithFileName(Resources::Menus_TitleScreen_Slime_Slime_0022_SlimeFrames030);
	this->slimeAnimation->addSpriteFrameWithFileName(Resources::Menus_TitleScreen_Slime_Slime_0023_SlimeFrames031);
	this->slimeAnimation->addSpriteFrameWithFileName(Resources::Menus_TitleScreen_Slime_Slime_0024_SlimeFrames032);
	this->slimeAnimation->addSpriteFrameWithFileName(Resources::Menus_TitleScreen_Slime_Slime_0025_SlimeFrames033);
	this->slimeAnimation->addSpriteFrameWithFileName(Resources::Menus_TitleScreen_Slime_Slime_0026_SlimeFrames034);
	this->slimeAnimation->addSpriteFrameWithFileName(Resources::Menus_TitleScreen_Slime_Slime_0027_SlimeFrames035);
	this->slimeAnimation->addSpriteFrameWithFileName(Resources::Menus_TitleScreen_Slime_Slime_0028_SlimeFrames036);
	this->slimeAnimation->addSpriteFrameWithFileName(Resources::Menus_TitleScreen_Slime_Slime_0029_SlimeFrames037);
	this->slimeAnimation->addSpriteFrameWithFileName(Resources::Menus_TitleScreen_Slime_Slime_0030_SlimeFrames038);
	this->slimeAnimation->addSpriteFrameWithFileName(Resources::Menus_TitleScreen_Slime_Slime_0031_SlimeFrames039);
	this->slimeAnimation->addSpriteFrameWithFileName(Resources::Menus_TitleScreen_Slime_Slime_0032_SlimeFrames040);
	this->slimeAnimation->addSpriteFrameWithFileName(Resources::Menus_TitleScreen_Slime_Slime_0033_SlimeFrames041);
	this->slimeAnimation->addSpriteFrameWithFileName(Resources::Menus_TitleScreen_Slime_Slime_0034_SlimeFrames042);
	this->slimeAnimation->addSpriteFrameWithFileName(Resources::Menus_TitleScreen_Slime_Slime_0035_SlimeFrames043);
	this->slimeAnimation->addSpriteFrameWithFileName(Resources::Menus_TitleScreen_Slime_Slime_0036_SlimeFrames044);
	this->slimeAnimation->addSpriteFrameWithFileName(Resources::Menus_TitleScreen_Slime_Slime_0037_SlimeFrames045);
}
