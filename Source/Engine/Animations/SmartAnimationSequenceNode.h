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

	static void primeCache(std::string initialSequenceResourceFile);

	SmartAnimationSequenceNode* clone();
	bool isPlayingAnimation();
	void stopAnimation();
	void playAnimation(std::string initialSequenceResourceFile, float animationSpeed, bool insertBlankFrame = false, std::function<void()> onAnimationComplete = nullptr);
	void playAnimation(std::vector<std::string> animationFiles, float animationSpeed, bool insertBlankFrame = false, std::function<void()> onAnimationComplete = nullptr);
	void playAnimationRepeat(std::string initialSequenceResourceFile, float animationSpeed, float repeatDelay = 0.0f, bool insertBlankFrame = false, int repeatCount = -1, std::function<void()> onAnimationComplete = nullptr);
	void playAnimationRepeat(std::vector<std::string> animationFiles, float animationSpeed, float repeatDelay = 0.0f, bool insertBlankFrame = false, int repeatCount = -1, std::function<void()> onAnimationComplete = nullptr);
	void playAnimationAndReverse(std::string initialSequenceResourceFile, float animationSpeedIn, float reverseDelay, float animationSpeedOut, bool insertBlankFrame = false, std::function<void()> onAnimationComplete = nullptr);
	void playAnimationAndReverse(std::vector<std::string> animationFiles, float animationSpeedIn, float reverseDelay, float animationSpeedOut, bool insertBlankFrame = false, std::function<void()> onAnimationComplete = nullptr);
	void playAnimationAndReverseRepeat(std::string initialSequenceResourceFile, float animationSpeedIn, float reverseDelay, float animationSpeedOut, float repeatDelay = 0.0f, bool insertBlankFrame = false, bool startReversed = false, int repeatCount = -1, std::function<void()> onAnimationComplete = nullptr);
	void playAnimationAndReverseRepeat(std::vector<std::string> animationFiles, float animationSpeedIn, float reverseDelay, float animationSpeedOut, float repeatDelay = 0.0f, bool insertBlankFrame = false, bool startReversed = false, int repeatCount = -1, std::function<void()> onAnimationComplete = nullptr);
	void setAnimationAnchor(cocos2d::Vec2 anchor);
	void setFlippedX(bool isFlipped);
	void setFlippedY(bool isFlipped);

protected:
	cocos2d::Sprite* sprite;

private:
	typedef SmartNode super;
	SmartAnimationSequenceNode(std::string defaultSprite);
	virtual ~SmartAnimationSequenceNode();

	std::string defaultSprite;
	bool hasPlayingAnimation;
	int repeatIndex;
	cocos2d::Vec2 animationAnchor;

	static std::map<std::string, std::vector<std::string>> AnimationFileCache;
	static std::vector<std::string> getAllAnimationFiles(std::string firstFrameResource);
};
