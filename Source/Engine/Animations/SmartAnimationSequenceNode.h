#pragma once
#include <functional>

#include "Engine/SmartNode.h"

// forward declarations
namespace cocos2d
{
	class Sprite;
}

class SmartAnimationSequenceNode : public SmartNode
{
public:
	static SmartAnimationSequenceNode* create();
	static SmartAnimationSequenceNode* create(std::string defaultSprite);

	SmartAnimationSequenceNode* clone();
	bool isPlayingAnimation();
	void stopAnimation();
	void playAnimation(std::string initialSequenceResourceFile, float animationSpeed, bool insertBlankFrame = false, std::function<void()> onAnimationComplete = nullptr);
	void playAnimation(const std::vector<std::string>& animationFiles, float animationSpeed, bool insertBlankFrame = false, std::function<void()> onAnimationComplete = nullptr);
	void playAnimationRepeat(std::string initialSequenceResourceFile, float animationSpeed, float repeatDelay = 0.0f, bool insertBlankFrame = false, int repeatCount = -1, std::function<void()> onAnimationComplete = nullptr);
	void playAnimationRepeat(const std::vector<std::string>& animationFiles, float animationSpeed, float repeatDelay = 0.0f, bool insertBlankFrame = false, int repeatCount = -1, std::function<void()> onAnimationComplete = nullptr);
	void playAnimationAndReverse(std::string initialSequenceResourceFile, float animationSpeedIn, float reverseDelay, float animationSpeedOut, bool insertBlankFrame = false, bool startReversed = false, std::function<void()> onAnimationComplete = nullptr);
	void playAnimationAndReverse(const std::vector<std::string>& animationFiles, float animationSpeedIn, float reverseDelay, float animationSpeedOut, bool insertBlankFrame = false, bool startReversed = false, std::function<void()> onAnimationComplete = nullptr);
	void playAnimationAndReverseRepeat(std::string initialSequenceResourceFile, float animationSpeedIn, float reverseDelay, float animationSpeedOut, float repeatDelay = 0.0f, bool insertBlankFrame = false, bool startReversed = false, int repeatCount = -1, std::function<void()> onAnimationComplete = nullptr);
	void playAnimationAndReverseRepeat(const std::vector<std::string>& animationFiles, float animationSpeedIn, float reverseDelay, float animationSpeedOut, float repeatDelay = 0.0f, bool insertBlankFrame = false, bool startReversed = false, int repeatCount = -1, std::function<void()> onAnimationComplete = nullptr);
	void setAnimationAnchor(cocos2d::Vec2 anchor);
	void setFlippedX(bool isFlipped);
	void setFlippedY(bool isFlipped);
	void setIncrementCallback(std::function<int(int, int)> incrementCallback);

	static void PrimeCache(std::string initialSequenceResourceFile);

protected:
	SmartAnimationSequenceNode(std::string defaultSprite);
	virtual ~SmartAnimationSequenceNode();

	cocos2d::Sprite* sprite;

private:
	typedef SmartNode super;

	std::string defaultSprite;
	bool hasPlayingAnimation;
	int repeatIndex;
	std::function<int(int, int)> incrementCallback;

	static std::map<std::string, std::vector<std::string>> AnimationFileCache;
	static const std::vector<std::string>& GetAllAnimationFiles(std::string firstFrameResource);
};
