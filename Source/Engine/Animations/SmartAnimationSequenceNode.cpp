#include "SmartAnimationSequenceNode.h"

#include "cocos/2d/CCAnimation.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/2d/CCAction.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/platform/CCFileUtils.h"

#include "Engine/Utils/StrUtils.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

std::map<std::string, std::vector<std::string>> SmartAnimationSequenceNode::AnimationFileCache = std::map<std::string, std::vector<std::string>>();

SmartAnimationSequenceNode* SmartAnimationSequenceNode::create(std::string defaultSprite)
{
	SmartAnimationSequenceNode* instance = new SmartAnimationSequenceNode(defaultSprite);

	instance->autorelease();

	return instance;
}

SmartAnimationSequenceNode* SmartAnimationSequenceNode::create()
{
	SmartAnimationSequenceNode* instance = new SmartAnimationSequenceNode();

	instance->autorelease();

	return instance;
}

SmartAnimationSequenceNode::SmartAnimationSequenceNode(std::string defaultSprite)
{
	this->sprite = Sprite::create(defaultSprite);
	this->forwardsAnimation = nullptr;
	this->backwardsAnimation = nullptr;

	this->addChild(this->sprite);
}

SmartAnimationSequenceNode::SmartAnimationSequenceNode()
{
	this->sprite = Sprite::create();
	this->forwardsAnimation = nullptr;
	this->backwardsAnimation = nullptr;

	this->addChild(this->sprite);
}

SmartAnimationSequenceNode::~SmartAnimationSequenceNode()
{
}

void SmartAnimationSequenceNode::primeCache(std::string initialSequenceResourceFile)
{
	SmartAnimationSequenceNode::getAllAnimationFiles(initialSequenceResourceFile);
}

void SmartAnimationSequenceNode::playAnimation(std::string initialSequenceResourceFile, float animationSpeed, bool insertBlankFrame, std::function<void()> onAnimationComplete)
{
	Animation* animation = Animation::create();
	auto animationFiles = SmartAnimationSequenceNode::getAllAnimationFiles(initialSequenceResourceFile);

	for (auto it = animationFiles.begin(); it != animationFiles.end(); it++)
	{
		animation->addSpriteFrameWithFile(*it);
	}

	if (insertBlankFrame)
	{
		animation->addSpriteFrameWithFile(UIResources::EmptyImage);
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

void SmartAnimationSequenceNode::playAnimationRepeat(std::string initialSequenceResourceFile, float animationSpeed, float repeatDelay, bool insertBlankFrame)
{
	Animation* animation = Animation::create();
	auto animationFiles = SmartAnimationSequenceNode::getAllAnimationFiles(initialSequenceResourceFile);

	for (auto it = animationFiles.begin(); it != animationFiles.end(); it++)
	{
		animation->addSpriteFrameWithFile(*it);
	}

	if (insertBlankFrame)
	{
		animation->addSpriteFrameWithFile(UIResources::EmptyImage);
	}

	animation->setDelayPerUnit(animationSpeed);

	this->forwardsAnimation = Animate::create(animation);

	this->sprite->stopAllActions();
	this->sprite->runAction(RepeatForever::create(Sequence::create(this->forwardsAnimation, DelayTime::create(repeatDelay), nullptr)));
}

void SmartAnimationSequenceNode::playAnimationAndReverse(std::string initialSequenceResourceFile, float animationSpeedIn, float reverseDelay, float animationSpeedOut, bool insertBlankFrame, std::function<void()> onAnimationComplete)
{
	Animation* animationIn = Animation::create();
	Animation* animationOut = Animation::create();
	auto animationFiles = SmartAnimationSequenceNode::getAllAnimationFiles(initialSequenceResourceFile);

	if (insertBlankFrame)
	{
		animationOut->addSpriteFrameWithFile(UIResources::EmptyImage);
	}

	for (auto it = animationFiles.begin(); it != animationFiles.end(); it++)
	{
		animationIn->addSpriteFrameWithFile(*it);
		animationOut->addSpriteFrameWithFile(*it);
	}

	if (insertBlankFrame)
	{
		animationIn->addSpriteFrameWithFile(UIResources::EmptyImage);
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

void SmartAnimationSequenceNode::playAnimationAndReverseRepeat(std::string initialSequenceResourceFile, float animationSpeedIn, float reverseDelay, float animationSpeedOut, float repeatDelay, bool insertBlankFrame, bool startReversed)
{
	Animation* animationIn = Animation::create();
	Animation* animationOut = Animation::create();
	auto animationFiles = SmartAnimationSequenceNode::getAllAnimationFiles(initialSequenceResourceFile);

	if (insertBlankFrame)
	{
		animationOut->addSpriteFrameWithFile(UIResources::EmptyImage);
	}

	for (auto it = animationFiles.begin(); it != animationFiles.end(); it++)
	{
		animationIn->addSpriteFrameWithFile(*it);
		animationOut->addSpriteFrameWithFile(*it);
	}

	if (insertBlankFrame)
	{
		animationIn->addSpriteFrameWithFile(UIResources::EmptyImage);
	}

	animationIn->setDelayPerUnit(animationSpeedIn);
	animationOut->setDelayPerUnit(animationSpeedOut);

	if (startReversed)
	{
		this->forwardsAnimation = Animate::create(animationIn)->reverse();
		this->backwardsAnimation = Animate::create(animationOut);

		this->sprite->stopAllActions();
		this->sprite->runAction(RepeatForever::create(Sequence::create(this->forwardsAnimation, DelayTime::create(repeatDelay), this->backwardsAnimation, DelayTime::create(reverseDelay), nullptr)));
	}
	else
	{
		this->forwardsAnimation = Animate::create(animationIn);
		this->backwardsAnimation = Animate::create(animationOut)->reverse();

		this->sprite->stopAllActions();
		this->sprite->runAction(RepeatForever::create(Sequence::create(this->forwardsAnimation, DelayTime::create(reverseDelay), this->backwardsAnimation, DelayTime::create(repeatDelay), nullptr)));
	}
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

	size_t extensionIndex = firstFrameResource.find_last_of(".");

	// Extract the base animation name from the provided animation resource (ie HARPY_WALKING_0001.png > HARPY_WALKING)
	// Note: The animations must follow the format of {ANIMATION_BASE}{INDEX}{EXTENSION}, with the index optionally leading w/ zeros
	std::string extensionlessBaseName = firstFrameResource.substr(0, extensionIndex);
	std::string extension = firstFrameResource.substr(extensionIndex, firstFrameResource.size());
	size_t lastIndex = extensionlessBaseName.find_last_not_of("0123456789");
	std::string animationNameBase = FileUtils::getInstance()->getDefaultResourceRootPath() + extensionlessBaseName.substr(0, lastIndex);
	std::string directoryName = FileUtils::getInstance()->getDefaultResourceRootPath() + firstFrameResource.substr(0, firstFrameResource.find_last_of("/\\"));

	// These files wont be sorted on the filesystem because strings do not sort like ints -- build an ordered map of int to string
	std::map<int, std::string> orderedAnimationFileMap = std::map<int, std::string>();
	std::vector<std::string> files = FileUtils::getInstance()->listFiles(directoryName);

	for (auto it = files.begin(); it != files.end(); it++)
	{
		std::string fileName = StrUtils::replaceAll(*it, "\\", "/");

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
				orderedAnimationFileMap.emplace(index, fileName);
			}
		}
	}

	std::vector<std::string> foundAnimations = std::vector<std::string>();

	for (auto it = orderedAnimationFileMap.begin(); it != orderedAnimationFileMap.end(); it++)
	{
		std::string fileName = it->second;

		foundAnimations.push_back(fileName);
	}

	SmartAnimationSequenceNode::AnimationFileCache[firstFrameResource] = foundAnimations;

	return foundAnimations;
}
