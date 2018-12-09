#include "StarLayer.h"

std::map<StarLayer::Stars, int> StarLayer::frequencyMap =
{
	{ StarLayer::Stars::StarSmall, 1000 },
	{ StarLayer::Stars::StarMedium, 1000 },
	{ StarLayer::Stars::StarLarge, 1000 },
	{ StarLayer::Stars::StarShineSmall, 200 },
	{ StarLayer::Stars::StarShineSmallHallow, 200 },
	{ StarLayer::Stars::StarShineLarge, 45 },
	{ StarLayer::Stars::StarShineExtraLarge, 25 },
};

StarLayer* StarLayer::create(Vec2 size)
{
	StarLayer* instance = new StarLayer(size);

	instance->autorelease();

	return instance;
}

StarLayer::StarLayer(Vec2 size)
{
	this->layerSize = size;

	this->setContentSize(this->layerSize);
}

StarLayer::~StarLayer()
{
}

void StarLayer::onEnter()
{
	Node::onEnter();

	this->scheduleUpdate();
	this->createStars();
}

void StarLayer::createStars()
{
	int frequencySum = 0;

	for (auto it = frequencyMap.begin(); it != frequencyMap.end(); it++)
	{
		frequencySum += it->second;
	}

	const float stepSize = 48;

	for (float x = 0; x < this->layerSize.width; x+= stepSize)
	{
		for (float y = 0; y < this->layerSize.height; y+= stepSize)
		{
			StarLayer::Stars star = StarLayer::Stars::StarSmall;
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
				nextSprite = Sprite::create(CutsceneResources::General_Stars_StarSmall);
				break;
			}
			case StarMedium:
			{
				nextSprite = Sprite::create(CutsceneResources::General_Stars_StarMedium);
				break;
			}
			case StarLarge:
			{
				nextSprite = Sprite::create(CutsceneResources::General_Stars_StarLarge);
				break;
			}
			case StarShineSmall:
			{
				nextSprite = Sprite::create(CutsceneResources::General_Stars_StarShineSmall_0000);

				Animation* animation = Animation::create();
				auto starFrames = GameUtils::getAllAnimationFiles(CutsceneResources::General_Stars_StarShineSmall_0000);
				bool reverse = RandomHelper::random_int(0, 1) < 1;

				for (auto it = starFrames.begin(); it != starFrames.end(); it++)
				{
					animation->addSpriteFrameWithFile(*it);
				}

				animation->setDelayPerUnit(RandomHelper::random_real(0.4f, 1.0f));
				nextSprite->runAction(RepeatForever::create(Sequence::create(reverse ? Animate::create(animation) : Animate::create(animation)->reverse(), nullptr)));
				break;
			}
			case StarShineSmallHallow:
			{
				nextSprite = Sprite::create(CutsceneResources::General_Stars_StarShineSmallHallow_0000);

				Animation* animation = Animation::create();
				auto starFrames = GameUtils::getAllAnimationFiles(CutsceneResources::General_Stars_StarShineSmallHallow_0000);
				bool reverse = RandomHelper::random_int(0, 1) < 1;

				for (auto it = starFrames.begin(); it != starFrames.end(); it++)
				{
					animation->addSpriteFrameWithFile(*it);
				}

				animation->setDelayPerUnit(RandomHelper::random_real(0.4f, 1.0f));
				nextSprite->runAction(RepeatForever::create(Sequence::create(reverse ? Animate::create(animation) : Animate::create(animation)->reverse(), nullptr)));
				break;
			}
			case StarShineLarge:
			{
				nextSprite = Sprite::create(CutsceneResources::General_Stars_StarShineLarge_0000);

				Animation* animation = Animation::create();
				auto starFrames = GameUtils::getAllAnimationFiles(CutsceneResources::General_Stars_StarShineLarge_0000);
				bool reverse = RandomHelper::random_int(0, 1) < 1;

				for (auto it = starFrames.begin(); it != starFrames.end(); it++)
				{
					animation->addSpriteFrameWithFile(*it);
				}

				animation->setDelayPerUnit(RandomHelper::random_real(0.4f, 1.0f));
				nextSprite->runAction(RepeatForever::create(Sequence::create(reverse ? Animate::create(animation) : Animate::create(animation)->reverse(), nullptr)));
				break;
			}
			case StarShineExtraLarge:
			{
				nextSprite = Sprite::create(CutsceneResources::General_Stars_StarShineExtraLarge_0000);

				Animation* animation = Animation::create();
				auto starFrames = GameUtils::getAllAnimationFiles(CutsceneResources::General_Stars_StarShineExtraLarge_0000);
				bool reverse = RandomHelper::random_int(0, 1) < 1;

				for (auto it = starFrames.begin(); it != starFrames.end(); it++)
				{
					animation->addSpriteFrameWithFile(*it);
				}

				animation->setDelayPerUnit(RandomHelper::random_real(0.4f, 1.0f));
				nextSprite->runAction(RepeatForever::create(Sequence::create(reverse ? Animate::create(animation) : Animate::create(animation)->reverse(), nullptr)));
				break;
			}
			}

			nextSprite->setScale(2);
			nextSprite->setPosition(x + RandomHelper::random_real(-stepSize * 4, stepSize * 4), y + RandomHelper::random_real(-stepSize * 4, stepSize * 4));

			this->addChild(nextSprite);
		}
	}
}
