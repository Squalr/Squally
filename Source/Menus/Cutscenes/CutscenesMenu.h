#pragma once
#include <functional>

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableTextNode;
class LabelStack;
class LocalizedLabel;
class LocalizedString;
class SmartAnimationSequenceNode;
class Sound;

enum class Cutscene
{
	None,
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
	void update(float dt) override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef SmartNode super;

	LocalizedLabel* buildHeader(LocalizedString* inText);
	LocalizedLabel* buildEntry(LocalizedString* inText);

	Cutscene currentCutscene = Cutscene::None;

	SmartAnimationSequenceNode* cutsceneAnimation = nullptr;
	ClickableTextNode* returnButton = nullptr;
	Sound* crackCutsceneChime = nullptr;
	Sound* tvOffSfx = nullptr;

	std::function<void()> returnClickCallback = nullptr;
	
	LabelStack* credits = nullptr;
};
