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

class SquallyUploadMars : public CutsceneClip
{
public:
	static SquallyUploadMars* create();

protected:
	SquallyUploadMars();
	~SquallyUploadMars();

private:
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

	void onDialogueShown();
	void runCutscene();
	void runCutscenePt2();
	void runCutscenePt3();

	cocos2d::Sprite* squally;
	cocos2d::Sprite* background;
	cocos2d::LayerColor* dialoguePlate;
	DialogueLabel* dialogue;
	cocos2d::Label* escapeLabel;

	static const cocos2d::Vec2 panOffset;
	int dialogueCount;
};
