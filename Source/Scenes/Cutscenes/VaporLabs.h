#pragma once
#include "cocos2d.h"

#include "Engine/Dialogue/Dialogue.h"
#include "Engine/Input/InputManager.h"
#include "Engine/Utils/GameUtils.h"
#include "Resources.h"
#include "Scenes/Cutscenes/Cutscene.h"
#include "Scenes/Cutscenes/Objects/StarLayer.h"

using namespace cocos2d;

class VaporLabs : public Cutscene
{
public:
	static VaporLabs* create();

protected:
	VaporLabs();
	~VaporLabs();

private:
	void onEnter() override;
	void update(float) override;
	void initializePositions();
	void initializeListeners();

	void cutscenePan();
	void onDialogueShown();
	void endCutscene();

	Node* contentLayer;
	LayerGradient* sky;
	StarLayer* starLayer;
	Sprite* cityView;
	Sprite* background;
	Sprite* console;
	Sprite* monitor;
	Sprite* scientist;

	LayerColor* dialoguePlate;
	Dialogue* dialogue;
	Label* escapeLabel;

	static const Vec2 panOffset;
};
