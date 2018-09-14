#pragma once
#include "cocos2d.h"

#include "Engine/Cutscenes/Cutscene.h"
#include "Engine/Dialogue/Dialogue.h"
#include "Engine/Input/InputManager.h"
#include "Engine/Utils/GameUtils.h"
#include "Resources.h"
#include "Scenes/Cutscenes/Objects/StarLayer.h"

using namespace cocos2d;

class SquallyUploadSpace : public Cutscene
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
	Sprite* mars;
	Node* beam;
	Sprite* satellite;
	LayerColor* dialoguePlate;
	Dialogue* dialogue;
	Label* escapeLabel;

	static const Vec2 panOffset;
};
