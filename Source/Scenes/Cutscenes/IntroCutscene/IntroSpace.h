#pragma once

#include "Engine/Cutscenes/CutsceneClip.h"

namespace cocos2d
{
	class Label;
	class LayerColor;
	class Sprite;
}

class DialogueLabel;
class SmartAnimationSequenceNode;
class StarLayer;

class IntroSpace : public CutsceneClip
{
public:
	static IntroSpace* create();

protected:
	IntroSpace();
	~IntroSpace();

private:
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void onDialogueShown();
	void runCutscene();

	StarLayer* starLayer;
	cocos2d::Sprite* earth;
	cocos2d::Sprite* mars;
	Node* weavers;
	SmartAnimationSequenceNode* weaver1;
	SmartAnimationSequenceNode* weaver2;
	SmartAnimationSequenceNode* weaver3;
	SmartAnimationSequenceNode* weaver4;
	SmartAnimationSequenceNode* weaver5;

	cocos2d::LayerColor* dialoguePlate;
	DialogueLabel* dialogue;
	cocos2d::Label* escapeLabel;

	static const float dialogueHeight;

	static const float earthDelta;
	static const float weaverDelta;
	static const float marsDelta;
};
