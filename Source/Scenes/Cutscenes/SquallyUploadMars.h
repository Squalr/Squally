#pragma once
#include "cocos2d.h"

#include "Engine/Dialogue/Dialogue.h"
#include "Engine/Input/InputManager.h"
#include "Engine/Utils/GameUtils.h"
#include "Resources.h"
#include "Scenes/Cutscenes/Cutscene.h"
#include "Scenes/Cutscenes/Objects/StarLayer.h"

using namespace cocos2d;

class SquallyUploadMars : public Cutscene
{
public:
	static SquallyUploadMars* create();

protected:
	SquallyUploadMars();
	~SquallyUploadMars();

private:
	void onEnter() override;
	void update(float) override;
	void initializePositions();
	void initializeListeners();

	void onDialogueShown();
	void runCutscene();
	void runCutscenePt2();
	void runCutscenePt3();
	void endCutscene();

	Sprite* squally;
	Sprite* background;
	LayerColor* dialoguePlate;
	Dialogue* dialogue;
	Label* escapeLabel;

	static const Vec2 panOffset;
	int dialogueCount;
};
