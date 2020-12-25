#include "SmartAnimationSequenceNode.h"

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

SmartAnimationSequenceNode* SmartAnimationSequenceNode::create(const std::string& defaultSprite)
{
	SmartAnimationSequenceNode* instance = new SmartAnimationSequenceNode(defaultSprite);

	instance->autorelease();

	return instance;
}

SmartAnimationSequenceNode::SmartAnimationSequenceNode(const std::string& defaultSprite)
{
	this->defaultSprite = defaultSprite;
	this->sprite = Sprite::create(this->defaultSprite);
	this->repeatIndex = 0;
	
	SmartAnimationSequenceNode::PrimeCache(this->defaultSprite);

	this->addChild(this->sprite);
}

SmartAnimationSequenceNode::~SmartAnimationSequenceNode()
{
}

SmartAnimationSequenceNode* SmartAnimationSequenceNode::clone()
{
	return SmartAnimationSequenceNode::create(this->defaultSprite);
}

void SmartAnimationSequenceNode::PrimeCache(const std::string& initialSequenceResourceFile)
{
	const std::vector<std::string>& images = SmartAnimationSequenceNode::GetAllAnimationFiles(initialSequenceResourceFile);

	for (const std::string& next : images)
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

void SmartAnimationSequenceNode::playSingleFrame(const std::string& initialSequenceResourceFile, int index, float animationSpeed, std::function<void()> onAnimationComplete)
{
	const std::vector<std::string>& animationFiles = SmartAnimationSequenceNode::GetAllAnimationFiles(initialSequenceResourceFile);

	this->playSingleFrame(animationFiles, index, animationSpeed, onAnimationComplete);
}

void SmartAnimationSequenceNode::playSingleFrame(const std::vector<std::string>& animationFiles, int index, float animationSpeed, std::function<void()> onAnimationComplete)
{
	// Delay then callback for out of range indexes
	if (index < 0 || index >= int(animationFiles.size()))
	{
		if (onAnimationComplete != nullptr)
		{
			this->sprite->runAction(Sequence::create(
				DelayTime::create(animationSpeed),
				CallFunc::create([=]()
				{
					onAnimationComplete();
				}),
				nullptr
			));
		}

		return;
	}

	std::vector<std::string> singleFrame = std::vector<std::string>{ animationFiles[index] };

	// Playing a 1 frame animation will complete instantly, so introduce a delay based on animation speed to call the callback
	this->playAnimation(singleFrame, animationSpeed, false, [=]()
	{
		if (onAnimationComplete != nullptr)
		{
			this->sprite->runAction(Sequence::create(
				DelayTime::create(animationSpeed),
				CallFunc::create([=]()
				{
					onAnimationComplete();
				}),
				nullptr
			));
		}
	});
}

void SmartAnimationSequenceNode::playAnimation(const std::string& initialSequenceResourceFile, float animationSpeed, bool insertBlankFrame, std::function<void()> onAnimationComplete)
{
	const std::vector<std::string>& animationFiles = SmartAnimationSequenceNode::GetAllAnimationFiles(initialSequenceResourceFile);

	this->playAnimation(animationFiles, animationSpeed, insertBlankFrame, onAnimationComplete);
}

void SmartAnimationSequenceNode::playAnimation(const std::vector<std::string>& animationFiles, float animationSpeed, bool insertBlankFrame, std::function<void()> onAnimationComplete)
{
	Vector<FiniteTimeAction*> animationSequence = Vector<FiniteTimeAction*>();

	for (const auto& animationFile : animationFiles)
	{
		animationSequence.pushBack(CallFunc::create([=]()
		{
			this->sprite->initWithFile(animationFile);
		}));

		if (&animationFile != &animationFiles.back())
		{
			animationSequence.pushBack(DelayTime::create(animationSpeed));
		}
	}

	if (insertBlankFrame)
	{
		animationSequence.pushBack(DelayTime::create(animationSpeed));
		animationSequence.pushBack(CallFunc::create([=]()
		{
			this->sprite->initWithFile(UIResources::EmptyImage);
		}));
	}

	animationSequence.pushBack(CallFunc::create([=]()
	{
		if (onAnimationComplete != nullptr)
		{
			onAnimationComplete();
		}
	}));

	this->sprite->stopAllActions();
	this->sprite->runAction(Sequence::create(animationSequence));
}

void SmartAnimationSequenceNode::playAnimationRepeat(const std::string& initialSequenceResourceFile, float animationSpeed, float repeatDelay, bool insertBlankFrame, int repeatCount, std::function<void()> onAnimationComplete)
{
	std::vector<std::string> animationFiles = SmartAnimationSequenceNode::GetAllAnimationFiles(initialSequenceResourceFile);

	this->playAnimationRepeat(animationFiles, animationSpeed, repeatDelay, insertBlankFrame, repeatCount, onAnimationComplete);
}

void SmartAnimationSequenceNode::playAnimationRepeat(const std::vector<std::string>& animationFiles, float animationSpeed, float repeatDelay, bool insertBlankFrame, int repeatCount, std::function<void()> onAnimationComplete)
{
	// Note: checking for exactly 0 as negative values are interpreted as repeat forever
	if (repeatCount == 0)
	{
		this->playAnimation(animationFiles, animationSpeed, insertBlankFrame, onAnimationComplete);
		return;
	}

	this->playAnimation(animationFiles, animationSpeed, insertBlankFrame, [=]()
	{
		if (repeatCount == 0)
		{
			if (onAnimationComplete != nullptr)
			{
				onAnimationComplete();
			}
		}
		else
		{
			this->sprite->runAction(Sequence::create(
				DelayTime::create(repeatDelay),
				CallFunc::create([=]()
				{
					int repeatCountNew = repeatCount < 0 ? repeatCount : (repeatCount - 1);
					this->playAnimationRepeat(animationFiles, animationSpeed, repeatDelay, insertBlankFrame, repeatCountNew, onAnimationComplete);
				}),
				nullptr
			));
		}
	});
}

void SmartAnimationSequenceNode::playAnimationAndReverse(const std::string& initialSequenceResourceFile, float animationSpeedIn, float reverseDelay, float animationSpeedOut, bool insertBlankFrame, bool startReversed, std::function<void()> onAnimationComplete)
{
	const std::vector<std::string>& animationFiles = SmartAnimationSequenceNode::GetAllAnimationFiles(initialSequenceResourceFile);

	this->playAnimationAndReverse(animationFiles, animationSpeedIn, reverseDelay, animationSpeedOut, insertBlankFrame, startReversed, onAnimationComplete);
}

void SmartAnimationSequenceNode::playAnimationAndReverse(const std::vector<std::string>& animationFiles, float animationSpeedIn, float reverseDelay, float animationSpeedOut, bool insertBlankFrame, bool startReversed, std::function<void()> onAnimationComplete)
{
	std::vector<std::string> animationFilesReverse = std::vector<std::string>(animationFiles.rbegin(), animationFiles.rend());

	this->playAnimation(startReversed ? animationFilesReverse : animationFiles, animationSpeedIn, insertBlankFrame, [=]
	{
		this->sprite->runAction(Sequence::create(
			DelayTime::create(reverseDelay),
			CallFunc::create([=]()
			{
				// No blank frame on animation out
				this->playAnimation(startReversed ? animationFiles : animationFilesReverse, animationSpeedIn, false, onAnimationComplete);
			}),
			nullptr
		));
	});
}

void SmartAnimationSequenceNode::playAnimationAndReverseRepeat(const std::string& initialSequenceResourceFile, float animationSpeedIn, float reverseDelay, float animationSpeedOut, float repeatDelay, bool insertBlankFrame, bool startReversed, int repeatCount, std::function<void()> onAnimationComplete)
{
	const std::vector<std::string>& animationFiles = SmartAnimationSequenceNode::GetAllAnimationFiles(initialSequenceResourceFile);

	this->playAnimationAndReverseRepeat(animationFiles, animationSpeedIn, reverseDelay, animationSpeedOut, repeatDelay, insertBlankFrame, startReversed, repeatCount, onAnimationComplete);
}

void SmartAnimationSequenceNode::playAnimationAndReverseRepeat(const std::vector<std::string>& animationFiles, float animationSpeedIn, float reverseDelay, float animationSpeedOut, float repeatDelay, bool insertBlankFrame, bool startReversed, int repeatCount, std::function<void()> onAnimationComplete)
{
	if (repeatCount == 0)
	{
		this->playAnimationAndReverse(animationFiles, animationSpeedIn, reverseDelay, insertBlankFrame, startReversed, animationSpeedOut, onAnimationComplete);
		return;
	}

	this->playAnimationAndReverse(animationFiles, animationSpeedIn, reverseDelay, insertBlankFrame, startReversed, animationSpeedOut, [=]()
	{
		if (repeatCount == 0)
		{
			if (onAnimationComplete != nullptr)
			{
				onAnimationComplete();
			}
		}
		else
		{
			this->sprite->runAction(Sequence::create(
				DelayTime::create(repeatDelay),
				CallFunc::create([=]()
				{
					int repeatCountNew = repeatCount < 0 ? repeatCount : (repeatCount - 1);
					this->playAnimationAndReverseRepeat(animationFiles, animationSpeedIn, reverseDelay, animationSpeedOut, repeatDelay, insertBlankFrame, startReversed, repeatCountNew, onAnimationComplete);
				}),
				nullptr
			));
		}
	});
}

void SmartAnimationSequenceNode::setAnimationAnchor(Vec2 anchor)
{
	this->sprite->setAnchorPoint(anchor);
}

void SmartAnimationSequenceNode::setFlippedX(bool isFlipped)
{
	this->sprite->setFlippedX(isFlipped);
}

void SmartAnimationSequenceNode::setFlippedY(bool isFlipped)
{
	this->sprite->setFlippedY(isFlipped);
}

int SmartAnimationSequenceNode::GetAnimationLength(const std::string& initialSequenceResourceFile)
{
	return SmartAnimationSequenceNode::GetAllAnimationFiles(initialSequenceResourceFile).size();
}

const std::vector<std::string>& SmartAnimationSequenceNode::GetAllAnimationFiles(const std::string& initialSequenceResourceFile)
{
	if (SmartAnimationSequenceNode::AnimationFileCache.find(initialSequenceResourceFile) != SmartAnimationSequenceNode::AnimationFileCache.end())
	{
		return SmartAnimationSequenceNode::AnimationFileCache[initialSequenceResourceFile];
	}

	// Normalize directory seperator
	std::string firstFrameResource = StrUtils::replaceAll(initialSequenceResourceFile, "\\", "/");
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

	for (const std::string& next : files)
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

	SmartAnimationSequenceNode::AnimationFileCache[firstFrameResource] = std::vector<std::string>();

	for (const auto& next : orderedAnimationFileMap)
	{
		std::string fileName = next.second;

		SmartAnimationSequenceNode::AnimationFileCache[firstFrameResource].push_back(fileName);
	}

	return SmartAnimationSequenceNode::AnimationFileCache[firstFrameResource];
}
