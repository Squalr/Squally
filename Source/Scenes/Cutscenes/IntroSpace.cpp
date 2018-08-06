#include "IntroSpace.h"

std::map<IntroSpace::Stars, int> IntroSpace::frequencyMap =
{
	{ IntroSpace::Stars::StarSmall, 1000 },
	{ IntroSpace::Stars::StarMedium, 1000 },
	{ IntroSpace::Stars::StarLarge, 1000 },
	{ IntroSpace::Stars::StarShineSmall, 200 },
	{ IntroSpace::Stars::StarShineSmallHallow, 200 },
	{ IntroSpace::Stars::StarShineLarge, 45 },
	{ IntroSpace::Stars::StarShineExtraLarge, 25 },
};

IntroSpace* IntroSpace::create()
{
	IntroSpace* instance = new IntroSpace();

	instance->autorelease();

	return instance;
}

IntroSpace::IntroSpace()
{
	this->starsLayer = Node::create();
	this->earth = Sprite::create(Resources::Cutscenes_IntroSpace_Earth);
	this->mars = Sprite::create(Resources::Cutscenes_IntroSpace_Mars);
	this->weaver1 = Sprite::create();
	this->weaver2 = Sprite::create();
	this->weaver3 = Sprite::create();
	this->weaver4 = Sprite::create();
	this->weaver5 = Sprite::create();
	this->weaver1Anim = Animation::create();
	this->weaver2Anim = Animation::create();
	this->weaver3Anim = Animation::create();
	this->weaver4Anim = Animation::create();
	this->weaver5Anim = Animation::create();

	this->weaver1->setScale(0.12);
	this->weaver2->setScale(0.14);
	this->weaver3->setScale(0.16);
	this->weaver4->setScale(0.18);
	this->weaver5->setScale(0.20);

	auto weaverFrames = GameUtils::getAllAnimationFiles(Resources::Cutscenes_IntroSpace_Weaver_0000);

	for (auto it = weaverFrames.begin(); it != weaverFrames.end(); it++)
	{
		this->weaver1Anim->addSpriteFrameWithFileName(*it);
		this->weaver2Anim->addSpriteFrameWithFileName(*it);
		this->weaver3Anim->addSpriteFrameWithFileName(*it);
		this->weaver4Anim->addSpriteFrameWithFileName(*it);
		this->weaver5Anim->addSpriteFrameWithFileName(*it);
	}

	this->weaver1->retain();
	this->weaver2->retain();
	this->weaver3->retain();
	this->weaver4->retain();
	this->weaver5->retain();

	this->addChild(InputManager::claimInstance());
	this->addChild(this->starsLayer);
	this->addChild(this->earth);
	this->addChild(this->mars);
	this->addChild(this->weaver1);
	this->addChild(this->weaver2);
	this->addChild(this->weaver3);
	this->addChild(this->weaver4);
	this->addChild(this->weaver5);
}

IntroSpace::~IntroSpace()
{
}

void IntroSpace::onEnter()
{
	Cutscene::onEnter();

	this->weaver1Anim->setDelayPerUnit(0.2f);
	this->weaver2Anim->setDelayPerUnit(0.225f);
	this->weaver3Anim->setDelayPerUnit(0.25f);
	this->weaver4Anim->setDelayPerUnit(0.275f);
	this->weaver5Anim->setDelayPerUnit(0.3f);

	this->weaver1->runAction(RepeatForever::create(Sequence::create(Animate::create(this->weaver1Anim), nullptr)));
	this->weaver2->runAction(RepeatForever::create(Sequence::create(Animate::create(this->weaver2Anim), nullptr)));
	this->weaver3->runAction(RepeatForever::create(Sequence::create(Animate::create(this->weaver3Anim), nullptr)));
	this->weaver4->runAction(RepeatForever::create(Sequence::create(Animate::create(this->weaver4Anim), nullptr)));
	this->weaver5->runAction(RepeatForever::create(Sequence::create(Animate::create(this->weaver5Anim), nullptr)));

	this->scheduleUpdate();
	this->createStars();
	this->initializePositions();
	this->initializeListeners();
}

void IntroSpace::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->mars->setAnchorPoint(Vec2(0.0f, 0.0f));
	this->mars->setPosition(Vec2(64.0f, 48.0f));
	this->earth->setAnchorPoint(Vec2(1.0f, 1.0f));
	this->earth->setPosition(Vec2(visibleSize.width - 32.0f, visibleSize.height - 32.0f));

	this->weaver1->setPosition(Vec2(visibleSize.width / 2.0f + 432.0f, visibleSize.height / 2.0f + 240.0f));
	this->weaver2->setPosition(Vec2(visibleSize.width / 2.0f + 384.0f, visibleSize.height / 2.0f + 224.0f));
	this->weaver3->setPosition(Vec2(visibleSize.width / 2.0f + 412.0f, visibleSize.height / 2.0f + 196.0f));
	this->weaver4->setPosition(Vec2(visibleSize.width / 2.0f + 368.0f, visibleSize.height / 2.0f + 188.0f));
	this->weaver5->setPosition(Vec2(visibleSize.width / 2.0f + 320.0f, visibleSize.height / 2.0f + 160.0f));
}

void IntroSpace::createStars()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	int frequencySum = 0;

	for (auto it = frequencyMap.begin(); it != frequencyMap.end(); it++)
	{
		frequencySum += it->second;
	}

	const int stepSize = 48;

	for (int x = 0; x < (int)visibleSize.width; x+= stepSize)
	{
		for (int y = 0; y < (int)visibleSize.height; y+= stepSize)
		{
			IntroSpace::Stars star = IntroSpace::Stars::StarSmall;
			int randStarFrequency = RandomHelper::random_int(0, frequencySum);
			int currentFrequencySum = 0;

			for (auto it = frequencyMap.begin(); it != frequencyMap.end(); it++)
			{
				currentFrequencySum += it->second;

				if (currentFrequencySum > randStarFrequency)
				{
					star = it->first;
					break;
				}
			}

			Sprite* nextSprite;

			switch (star)
			{
			default:
			case StarSmall:
			{
				nextSprite = Sprite::create(Resources::Cutscenes_IntroSpace_StarSmall);
				break;
			}
			case StarMedium:
			{
				nextSprite = Sprite::create(Resources::Cutscenes_IntroSpace_StarMedium);
				break;
			}
			case StarLarge:
			{
				nextSprite = Sprite::create(Resources::Cutscenes_IntroSpace_StarLarge);
				break;
			}
			case StarShineSmall:
			{
				nextSprite = Sprite::create(Resources::Cutscenes_IntroSpace_StarShineSmall_0000);

				Animation* animation = Animation::create();
				auto starFrames = GameUtils::getAllAnimationFiles(Resources::Cutscenes_IntroSpace_StarShineSmall_0000);
				bool reverse = RandomHelper::random_int(0, 1) < 1;

				for (auto it = starFrames.begin(); it != starFrames.end(); it++)
				{
					animation->addSpriteFrameWithFileName(*it);
				}

				animation->setDelayPerUnit(RandomHelper::random_real(0.4f, 1.0f));
				nextSprite->runAction(RepeatForever::create(Sequence::create(reverse ? Animate::create(animation) : Animate::create(animation)->reverse(), nullptr)));
				break;
			}
			case StarShineSmallHallow:
			{
				nextSprite = Sprite::create(Resources::Cutscenes_IntroSpace_StarShineSmallHallow_0000);

				Animation* animation = Animation::create();
				auto starFrames = GameUtils::getAllAnimationFiles(Resources::Cutscenes_IntroSpace_StarShineSmallHallow_0000);
				bool reverse = RandomHelper::random_int(0, 1) < 1;

				for (auto it = starFrames.begin(); it != starFrames.end(); it++)
				{
					animation->addSpriteFrameWithFileName(*it);
				}

				animation->setDelayPerUnit(RandomHelper::random_real(0.4f, 1.0f));
				nextSprite->runAction(RepeatForever::create(Sequence::create(reverse ? Animate::create(animation) : Animate::create(animation)->reverse(), nullptr)));
				break;
			}
			case StarShineLarge:
			{
				nextSprite = Sprite::create(Resources::Cutscenes_IntroSpace_StarShineLarge_0000);

				Animation* animation = Animation::create();
				auto starFrames = GameUtils::getAllAnimationFiles(Resources::Cutscenes_IntroSpace_StarShineLarge_0000);
				bool reverse = RandomHelper::random_int(0, 1) < 1;

				for (auto it = starFrames.begin(); it != starFrames.end(); it++)
				{
					animation->addSpriteFrameWithFileName(*it);
				}

				animation->setDelayPerUnit(RandomHelper::random_real(0.4f, 1.0f));
				nextSprite->runAction(RepeatForever::create(Sequence::create(reverse ? Animate::create(animation) : Animate::create(animation)->reverse(), nullptr)));
				break;
			}
			case StarShineExtraLarge:
			{
				nextSprite = Sprite::create(Resources::Cutscenes_IntroSpace_StarShineExtraLarge_0000);

				Animation* animation = Animation::create();
				auto starFrames = GameUtils::getAllAnimationFiles(Resources::Cutscenes_IntroSpace_StarShineExtraLarge_0000);
				bool reverse = RandomHelper::random_int(0, 1) < 1;

				for (auto it = starFrames.begin(); it != starFrames.end(); it++)
				{
					animation->addSpriteFrameWithFileName(*it);
				}

				animation->setDelayPerUnit(RandomHelper::random_real(0.4f, 1.0f));
				nextSprite->runAction(RepeatForever::create(Sequence::create(reverse ? Animate::create(animation) : Animate::create(animation)->reverse(), nullptr)));
				break;
			}
			}

			nextSprite->setScale(2);
			nextSprite->setPosition(x + RandomHelper::random_int(-stepSize * 4, stepSize * 4), y + RandomHelper::random_int(-stepSize * 4, stepSize * 4));

			this->starsLayer->addChild(nextSprite);
		}
	}
}

void IntroSpace::initializeListeners()
{
	this->getEventDispatcher()->removeEventListenersForTarget(this);
}

void IntroSpace::update(float dt)
{
	FadeScene::update(dt);

	if (InputManager::getInstance()->isPressed(EventKeyboard::KeyCode::KEY_ESCAPE))
	{
		this->endCutscene();
	}
}

void IntroSpace::endCutscene()
{
	NavigationEvents::loadMap(Resources::Maps_Isometric_Sanctum);
}
