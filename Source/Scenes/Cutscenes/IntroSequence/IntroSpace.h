#pragma once
#include "cocos2d.h"

#include "Engine/Cutscenes/Cutscene.h"
#include "Engine/Dialogue/Dialogue.h"
#include "Engine/Input/InputManager.h"
#include "Engine/Utils/GameUtils.h"
#include "Resources.h"
#include "Scenes/Cutscenes/Objects/StarLayer.h"

using namespace cocos2d;

class IntroSpace : public Cutscene
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
	Sprite* earth;
	Sprite* mars;
	Node* weavers;
	Sprite* weaver1;
	Animation* weaver1Anim;
	Sprite* weaver2;
	Animation* weaver2Anim;
	Sprite* weaver3;
	Animation* weaver3Anim;
	Sprite* weaver4;
	Animation* weaver4Anim;
	Sprite* weaver5;
	Animation* weaver5Anim;

	LayerColor* dialoguePlate;
	Dialogue* dialogue;
	Label* escapeLabel;

	static const float dialogueHeight;

	static const float earthDelta;
	static const float weaverDelta;
	static const float marsDelta;
};
