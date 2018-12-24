#include "StarLayer.h"

#include "cocos/2d/CCAction.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCLayer.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/CutsceneResources.h"

using namespace cocos2d;

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

			Node* nextSprite;

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
					SmartAnimationSequenceNode* animation = SmartAnimationSequenceNode::create(CutsceneResources::General_Stars_StarShineSmall_0000);

					float animationSpeed = RandomHelper::random_real(0.4f, 1.0f);
					bool reverse = RandomHelper::random_int(0, 1) < 1;

					animation->playAnimationAndReverseRepeat(CutsceneResources::General_Stars_StarShineSmall_0000, animationSpeed, 0.0f, animationSpeed, 0.0f, reverse);

					nextSprite = animation;
					break;
				}
				case StarShineSmallHallow:
				{
					SmartAnimationSequenceNode* animation = SmartAnimationSequenceNode::create(CutsceneResources::General_Stars_StarShineSmallHallow_0000);

					float animationSpeed = RandomHelper::random_real(0.4f, 1.0f);
					bool reverse = RandomHelper::random_int(0, 1) < 1;

					animation->playAnimationAndReverseRepeat(CutsceneResources::General_Stars_StarShineSmallHallow_0000, animationSpeed, 0.0f, animationSpeed, 0.0f, reverse);

					nextSprite = animation;
					break;
				}
				case StarShineLarge:
				{
					SmartAnimationSequenceNode* animation = SmartAnimationSequenceNode::create(CutsceneResources::General_Stars_StarShineLarge_0000);

					float animationSpeed = RandomHelper::random_real(0.4f, 1.0f);
					bool reverse = RandomHelper::random_int(0, 1) < 1;

					animation->playAnimationAndReverseRepeat(CutsceneResources::General_Stars_StarShineLarge_0000, animationSpeed, 0.0f, animationSpeed, 0.0f, reverse);

					nextSprite = animation;
					break;
				}
				case StarShineExtraLarge:
				{
					SmartAnimationSequenceNode* animation = SmartAnimationSequenceNode::create(CutsceneResources::General_Stars_StarShineExtraLarge_0000);

					float animationSpeed = RandomHelper::random_real(0.4f, 1.0f);
					bool reverse = RandomHelper::random_int(0, 1) < 1;

					animation->playAnimationAndReverseRepeat(CutsceneResources::General_Stars_StarShineExtraLarge_0000, animationSpeed, 0.0f, animationSpeed, 0.0f, reverse);

					nextSprite = animation;
					break;
				}
			}

			nextSprite->setScale(2);
			nextSprite->setPosition(x + RandomHelper::random_real(-stepSize * 4, stepSize * 4), y + RandomHelper::random_real(-stepSize * 4, stepSize * 4));

			this->addChild(nextSprite);
		}
	}
}
