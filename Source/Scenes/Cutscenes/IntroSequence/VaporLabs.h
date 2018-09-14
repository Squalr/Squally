#pragma once
#include "cocos2d.h"

#include "Engine/Cutscenes/Cutscene.h"
#include "Engine/Dialogue/Dialogue.h"
#include "Engine/Input/InputManager.h"
#include "Engine/Utils/GameUtils.h"
#include "Resources.h"
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
	void initializePositions() override;
	void initializeListeners() override;

	void runCutscene();
	void onDialogueShown();

	Node* contentLayer;
	LayerGradient* sky;
	StarLayer* starLayer;
	Sprite* cityView;
	Sprite* background;
	Sprite* console;
	Sprite* monitor;
	Sprite* scientist;

	LayerColor* siren;

	LayerColor* dialoguePlate;
	Dialogue* dialogue;
	Label* escapeLabel;

	static const Vec2 panOffset;
};
