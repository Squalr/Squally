#include "SmartAnimationSequenceNode.h"

#include "cocos/2d/CCAnimation.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/2d/CCAction.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/renderer/CCTextureCache.h"
#include "cocos/base/CCDirector.h"
#include "cocos/platform/CCFileUtils.h"

#include "Engine/Utils/StrUtils.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

std::map<std::string, std::vector<std::string>> SmartAnimationSequenceNode::AnimationFileCache = std::map<std::string, std::vector<std::string>>();

SmartAnimationSequenceNode* SmartAnimationSequenceNode::create()
{
	return SmartAnimationSequenceNode::create(UIResources::EmptyImage);
}

SmartAnimationSequenceNode* SmartAnimationSequenceNode::create(std::string defaultSprite)
{
	SmartAnimationSequenceNode* instance = new SmartAnimationSequenceNode(defaultSprite);

	instance->autorelease();

	return instance;
}

SmartAnimationSequenceNode::SmartAnimationSequenceNode(std::string defaultSprite)
{
	this->defaultSprite = defaultSprite;
	this->sprite = Sprite::create(this->defaultSprite);
	this->forwardsAnimation = nullptr;
	this->backwardsAnimation = nullptr;
	this->repeatIndex = 0;
	this->animationAnchor = Vec2(0.5f, 0.5f);
	
	this->primeCache(this->defaultSprite);

	this->addChild(this->sprite);
}

SmartAnimationSequenceNode::~SmartAnimationSequenceNode()
{
}

SmartAnimationSequenceNode* SmartAnimationSequenceNode::clone()
{
	return SmartAnimationSequenceNode::create(this->defaultSprite);
}

void SmartAnimationSequenceNode::primeCache(std::string initialSequenceResourceFile)
{
	std::vector<std::string> images = SmartAnimationSequenceNode::getAllAnimationFiles(initialSequenceResourceFile);

	for (auto next : images)
	{
		Director::getInstance()->getTextureCache()->addImage(next);
	}
}

bool SmartAnimationSequenceNode::isPlayingAnimation()
{
	return this->sprite != nullptr && this->sprite->getNumberOfRunningActions() != 0;
}

void SmartAnimationSequenceNode::stopAnimation()
{
	this->sprite->stopAllActions();

	if (this->defaultSprite.empty())
	{
		this->sprite->initWithFile(UIResources::EmptyImage);
	}
	else
	{
		this->sprite->initWithFile(this->defaultSprite);
	}
	
}

void SmartAnimationSequenceNode::playAnimation(std::string initialSequenceResourceFile, float animationSpeed, bool insertBlankFrame, std::function<void()> onAnimationComplete)
{
	std::vector<std::string> animationFiles = SmartAnimationSequenceNode::getAllAnimationFiles(initialSequenceResourceFile);

	this->playAnimation(animationFiles, animationSpeed, insertBlankFrame, onAnimationComplete);
}

void SmartAnimationSequenceNode::playAnimation(std::vector<std::string> animationFiles, float animationSpeed, bool insertBlankFrame, std::function<void()> onAnimationComplete)
{
	Animation* animation = Animation::create();

	for (auto next : animationFiles)
	{
		animation->addSpriteFrameWithFile(next);
	}

	if (insertBlankFrame)
	{
		animation->addSpriteFrameWithFile(UIResources::EmptyImage);
	}

	for (auto next : animation->getFrames())
	{
		if (next->getSpriteFrame() != nullptr)
		{
			next->getSpriteFrame()->setAnchorPoint(this->animationAnchor);
		}
	}

	animation->setDelayPerUnit(animationSpeed);

	this->forwardsAnimation = Animate::create(animation);

	this->sprite->stopAllActions();
	this->sprite->runAction(Sequence::create(
		this->forwardsAnimation,
		CallFunc::create([=]()
		{
			if (onAnimationComplete != nullptr)
			{
				onAnimationComplete();
			}
		}),
		nullptr
	));
}

void SmartAnimationSequenceNode::playAnimationRepeat(std::string initialSequenceResourceFile, float animationSpeed, float repeatDelay, bool insertBlankFrame, int repeatCount, std::function<void()> onAnimationComplete)
{
	std::vector<std::string> animationFiles = SmartAnimationSequenceNode::getAllAnimationFiles(initialSequenceResourceFile);

	this->playAnimationRepeat(animationFiles, animationSpeed, repeatDelay, insertBlankFrame, repeatCount, onAnimationComplete);
}

void SmartAnimationSequenceNode::playAnimationRepeat(std::vector<std::string> animationFiles, float animationSpeed, float repeatDelay, bool insertBlankFrame, int repeatCount, std::function<void()> onAnimationComplete)
{
	Animation* animation = Animation::create();

	for (auto next : animationFiles)
	{
		animation->addSpriteFrameWithFile(next);
	}

	if (insertBlankFrame)
	{
		animation->addSpriteFrameWithFile(UIResources::EmptyImage);
	}

	for (auto next : animation->getFrames())
	{
		if (next->getSpriteFrame() != nullptr)
		{
			next->getSpriteFrame()->setAnchorPoint(this->animationAnchor);
		}
	}

	animation->setDelayPerUnit(animationSpeed);

	this->forwardsAnimation = Animate::create(animation);

	this->sprite->stopAllActions();

	if (repeatCount <= 0)
	{
		this->sprite->runAction(RepeatForever::create(Sequence::create(this->forwardsAnimation, DelayTime::create(repeatDelay), nullptr)));
	}
	else
	{
		this->repeatIndex = 0;

		this->sprite->runAction(Repeat::create(
			Sequence::create(
				this->forwardsAnimation,
				DelayTime::create(repeatDelay),
				CallFunc::create([=]()
				{
					this->repeatIndex++;

					if (this->repeatIndex == repeatCount && onAnimationComplete != nullptr)
					{
						onAnimationComplete();
					}
				}),
				nullptr
			),
			repeatCount
		));
	}
}

void SmartAnimationSequenceNode::playAnimationAndReverse(std::string initialSequenceResourceFile, float animationSpeedIn, float reverseDelay, float animationSpeedOut, bool insertBlankFrame, std::function<void()> onAnimationComplete)
{
	std::vector<std::string> animationFiles = SmartAnimationSequenceNode::getAllAnimationFiles(initialSequenceResourceFile);

	this->playAnimationAndReverse(animationFiles, animationSpeedIn, reverseDelay, animationSpeedOut, insertBlankFrame, onAnimationComplete);
}

void SmartAnimationSequenceNode::playAnimationAndReverse(std::vector<std::string> animationFiles, float animationSpeedIn, float reverseDelay, float animationSpeedOut, bool insertBlankFrame, std::function<void()> onAnimationComplete)
{
	Animation* animationIn = Animation::create();
	Animation* animationOut = Animation::create();

	if (insertBlankFrame)
	{
		animationOut->addSpriteFrameWithFile(UIResources::EmptyImage);
	}

	for (auto next : animationFiles)
	{
		animationIn->addSpriteFrameWithFile(next);
		animationOut->addSpriteFrameWithFile(next);
	}

	if (insertBlankFrame)
	{
		animationIn->addSpriteFrameWithFile(UIResources::EmptyImage);
	}

	for (auto next : animationIn->getFrames())
	{
		if (next->getSpriteFrame() != nullptr)
		{
			next->getSpriteFrame()->setAnchorPoint(this->animationAnchor);
		}
	}

	for (auto next : animationOut->getFrames())
	{
		if (next->getSpriteFrame() != nullptr)
		{
			next->getSpriteFrame()->setAnchorPoint(this->animationAnchor);
		}
	}

	animationIn->setDelayPerUnit(animationSpeedIn);
	animationOut->setDelayPerUnit(animationSpeedOut);

	this->forwardsAnimation = Animate::create(animationIn);
	this->backwardsAnimation = Animate::create(animationOut)->reverse();

	this->sprite->stopAllActions();
	this->sprite->runAction(Sequence::create(
		this->forwardsAnimation,
		DelayTime::create(reverseDelay),
		this->backwardsAnimation,
		CallFunc::create([=]()
		{
			if (onAnimationComplete != nullptr)
			{
				onAnimationComplete();
			}
		}),
		nullptr
	));
}

void SmartAnimationSequenceNode::playAnimationAndReverseRepeat(std::string initialSequenceResourceFile, float animationSpeedIn, float reverseDelay, float animationSpeedOut, float repeatDelay, bool insertBlankFrame, bool startReversed, int repeatCount, std::function<void()> onAnimationComplete)
{
	std::vector<std::string> animationFiles = SmartAnimationSequenceNode::getAllAnimationFiles(initialSequenceResourceFile);

	this->playAnimationAndReverseRepeat(animationFiles, animationSpeedIn, reverseDelay, animationSpeedOut, repeatDelay, insertBlankFrame, startReversed, repeatCount, onAnimationComplete);
}

void SmartAnimationSequenceNode::playAnimationAndReverseRepeat(std::vector<std::string> animationFiles, float animationSpeedIn, float reverseDelay, float animationSpeedOut, float repeatDelay, bool insertBlankFrame, bool startReversed, int repeatCount, std::function<void()> onAnimationComplete)
{
	Animation* animationIn = Animation::create();
	Animation* animationOut = Animation::create();

	if (insertBlankFrame)
	{
		animationOut->addSpriteFrameWithFile(UIResources::EmptyImage);
	}

	for (auto next : animationFiles)
	{
		animationIn->addSpriteFrameWithFile(next);
		animationOut->addSpriteFrameWithFile(next);
	}

	if (insertBlankFrame)
	{
		animationIn->addSpriteFrameWithFile(UIResources::EmptyImage);
	}

	for (auto next : animationIn->getFrames())
	{
		if (next->getSpriteFrame() != nullptr)
		{
			next->getSpriteFrame()->setAnchorPoint(this->animationAnchor);
		}
	}

	for (auto next : animationOut->getFrames())
	{
		if (next->getSpriteFrame() != nullptr)
		{
			next->getSpriteFrame()->setAnchorPoint(this->animationAnchor);
		}
	}

	animationIn->setDelayPerUnit(animationSpeedIn);
	animationOut->setDelayPerUnit(animationSpeedOut);

	this->forwardsAnimation = Animate::create(animationIn);
	this->backwardsAnimation = Animate::create(animationOut)->reverse();
	this->sprite->stopAllActions();

	if (startReversed)
	{
		if (repeatCount <= 0)
		{
			this->sprite->runAction(RepeatForever::create(
				Sequence::create(
					this->backwardsAnimation,
					DelayTime::create(repeatDelay),
					this->forwardsAnimation,
					DelayTime::create(reverseDelay),
					CallFunc::create([=]()
					{
						if (onAnimationComplete != nullptr)
						{
							onAnimationComplete();
						}
					}),
					nullptr
				)
			));
		}
		else
		{
			this->sprite->runAction(Repeat::create(
				Sequence::create(
					this->backwardsAnimation,
					DelayTime::create(repeatDelay),
					this->forwardsAnimation,
					DelayTime::create(reverseDelay),
					CallFunc::create([=]()
					{
						this->repeatIndex++;

						if (this->repeatIndex == repeatCount && onAnimationComplete != nullptr)
						{
							onAnimationComplete();
						}
					}),
					nullptr
				),
				repeatCount
			));
		}
	}
	else
	{
		if (repeatCount <= 0)
		{
			this->sprite->runAction(RepeatForever::create(
				Sequence::create(
					this->forwardsAnimation,
					DelayTime::create(reverseDelay),
					this->backwardsAnimation,
					DelayTime::create(repeatDelay),
					CallFunc::create([=]()
					{
						if (onAnimationComplete != nullptr)
						{
							onAnimationComplete();
						}
					}),
					nullptr
				)
			));
		}
		else
		{
			this->repeatIndex = 0;

			this->sprite->runAction(Repeat::create(
				Sequence::create(
					this->forwardsAnimation,
					DelayTime::create(reverseDelay),
					this->backwardsAnimation,
					DelayTime::create(repeatDelay),
					CallFunc::create([=]()
					{
						this->repeatIndex++;

						if (this->repeatIndex == repeatCount && onAnimationComplete != nullptr)
						{
							onAnimationComplete();
						}
					}),
					nullptr
				),
				repeatCount
			));
		}
	}
}

void SmartAnimationSequenceNode::setAnimationAnchor(Vec2 anchor)
{
	this->animationAnchor = anchor;
}

void SmartAnimationSequenceNode::setFlippedX(bool isFlipped)
{
	this->sprite->setFlippedX(isFlipped);
}

void SmartAnimationSequenceNode::setFlippedY(bool isFlipped)
{
	this->sprite->setFlippedY(isFlipped);
}

Animate* SmartAnimationSequenceNode::getForwardsAnimation()
{
	return this->forwardsAnimation;
}

Animate* SmartAnimationSequenceNode::getBackwardsAnimation()
{
	return this->backwardsAnimation;
}

std::vector<std::string> SmartAnimationSequenceNode::getAllAnimationFiles(std::string firstFrameResource)
{
	if (SmartAnimationSequenceNode::AnimationFileCache.find(firstFrameResource) != SmartAnimationSequenceNode::AnimationFileCache.end())
	{
		return SmartAnimationSequenceNode::AnimationFileCache[firstFrameResource];
	}

	// Normalize directory seperator
	firstFrameResource = StrUtils::replaceAll(firstFrameResource, "\\", "/");
	std::string containingFolder = FileUtils::getInstance()->fullPathForFilename(firstFrameResource);
	containingFolder = containingFolder.substr(0, containingFolder.find_last_of("/\\")) + "/";

	// Extract the base animation name from the provided animation resource (ie HARPY_WALKING_0001.png > HARPY_WALKING)
	// Note: The animations must follow the format of {ANIMATION_BASE}{INDEX}{EXTENSION}, with the index optionally leading w/ zeros
	std::string extensionlessBaseName = firstFrameResource.substr(firstFrameResource.find_last_of("/\\") + 1, std::string::npos);
	extensionlessBaseName = extensionlessBaseName.substr(0, extensionlessBaseName.find_last_of("."));
	std::string extension = firstFrameResource.substr(firstFrameResource.find_last_of("."), std::string::npos);
	std::string animationNameBase = containingFolder + extensionlessBaseName.substr(0, extensionlessBaseName.find_last_not_of("0123456789"));

	// These files wont be sorted on the filesystem because strings do not sort like ints -- build an ordered map of int to string
	std::map<int, std::string> orderedAnimationFileMap = std::map<int, std::string>();
	std::vector<std::string> files = FileUtils::getInstance()->listFiles(containingFolder);

	for (auto next : files)
	{
		std::string fileName = StrUtils::replaceAll(next, "\\", "/");

		// Check if the file name matches the format of 
		if (StrUtils::startsWith(fileName, animationNameBase, true) && StrUtils::endsWith(fileName, extension, true))
		{
			// Extract the frame number and cast it to an integer
			std::string fileNameNoExtension = fileName.substr(0, fileName.find_last_of("."));
			std::string animationFrameIndex = fileNameNoExtension.substr(fileNameNoExtension.find_last_not_of("0123456789") + 1);

			// Should always be an int, but just in case
			if (StrUtils::isInteger(animationFrameIndex))
			{
				int index = std::stoi(animationFrameIndex);

				// Now that we have the actual index as an integer, store it in our mapping
				orderedAnimationFileMap[index] = fileName;
			}
		}
	}

	std::vector<std::string> foundAnimations = std::vector<std::string>();

	for (auto next : orderedAnimationFileMap)
	{
		std::string fileName = next.second;

		foundAnimations.push_back(fileName);
	}

	SmartAnimationSequenceNode::AnimationFileCache[firstFrameResource] = foundAnimations;

	return foundAnimations;
}
