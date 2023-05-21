#pragma once
#include <functional>

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableTextNode;
class SmartAnimationSequenceNode;
class Sound;

enum class Cutscene
{
	CrackSmall,
	CrackMedium,
	CrackLarge,
	Credits,
};

class CutscenesMenu : public SmartNode
{
public:
	static CutscenesMenu* create();

	void setReturnClickCallback(std::function<void()> returnClickCallback);
	void open(Cutscene cutscene);

protected:
	CutscenesMenu();
	virtual ~CutscenesMenu();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef SmartNode super;

	SmartAnimationSequenceNode* cutsceneAnimation = nullptr;
	ClickableTextNode* returnButton = nullptr;
	Sound* crackCutsceneChime = nullptr;

	std::function<void()> returnClickCallback = nullptr;
};
