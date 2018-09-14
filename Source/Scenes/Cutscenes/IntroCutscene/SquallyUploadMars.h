#pragma once
#include "cocos2d.h"

#include "Engine/Cutscenes/CutsceneClip.h"
#include "Engine/Dialogue/Dialogue.h"
#include "Engine/Utils/GameUtils.h"
#include "Resources.h"
#include "Scenes/Cutscenes/Objects/StarLayer.h"

using namespace cocos2d;

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

	Sprite* squally;
	Sprite* background;
	LayerColor* dialoguePlate;
	Dialogue* dialogue;
	Label* escapeLabel;

	static const Vec2 panOffset;
	int dialogueCount;
};
