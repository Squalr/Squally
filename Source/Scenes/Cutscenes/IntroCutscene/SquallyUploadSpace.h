#pragma once
#include "cocos/math/Vec2.h"

#include "Engine/Cutscenes/CutsceneClip.h"

namespace cocos2d
{
	class Label;
	class LayerColor;
	class Sprite;
}

class DialogueLabel;
class StarLayer;

class SquallyUploadSpace : public CutsceneClip
{
public:
	static SquallyUploadSpace* create();

protected:
	SquallyUploadSpace();
	~SquallyUploadSpace();

private:
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

	void onDialogueShown();
	void runCutscene();

	StarLayer* starLayer;
	cocos2d::Sprite* mars;
	cocos2d::Node* beam;
	cocos2d::Sprite* satellite;
	cocos2d::LayerColor* dialoguePlate;
	DialogueLabel* dialogue;
	cocos2d::Label* escapeLabel;

	static const cocos2d::Vec2 panOffset;
};
