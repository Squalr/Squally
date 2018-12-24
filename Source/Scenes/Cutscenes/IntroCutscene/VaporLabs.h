#pragma once
#include "cocos/2d/CCSprite.h"
#include "cocos/math/Vec2.h"

#include "Engine/Cutscenes/CutsceneClip.h"

namespace cocos2d
{
	class LayerColor;
	class LayerGradient;
	class Sprite;
}

class DialogueLabel;
class LocalizedLabel;
class StarLayer;

class VaporLabs : public CutsceneClip
{
public:
	static VaporLabs* create();

protected:
	VaporLabs();
	~VaporLabs();

private:
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

	void runCutscene();
	void onDialogueShown();

	cocos2d::Node* contentLayer;
	cocos2d::LayerGradient* sky;
	StarLayer* starLayer;
	cocos2d::Sprite* cityView;
	cocos2d::Sprite* background;
	cocos2d::Sprite* console;
	cocos2d::Sprite* monitor;
	cocos2d::Sprite* scientist;

	cocos2d::LayerColor* siren;

	cocos2d::LayerColor* dialoguePlate;
	DialogueLabel* dialogue;
	LocalizedLabel* escapeLabel;

	static const cocos2d::Vec2 panOffset;
};
