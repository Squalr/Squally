#pragma once
#include "cocos2d.h"

#include "Engine/Dialogue/Dialogue.h"
#include "Engine/Input/InputManager.h"
#include "Engine/Utils/GameUtils.h"
#include "Resources.h"
#include "Scenes/Cutscenes/Cutscene.h"
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
	void update(float) override;
	void initializePositions();
	void initializeListeners();
	void onDialogueShown();
	void runCutscene();
	void endCutscene();

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
