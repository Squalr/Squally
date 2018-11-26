#pragma once
#include "cocos2d.h"

#include "Engine/Cutscenes/CutsceneClip.h"
#include "Engine/Dialogue/Dialogue.h"
#include "Engine/Utils/GameUtils.h"
#include "Resources/CutsceneResources.h"
#include "Resources/StringResources.h"
#include "Scenes/Cutscenes/Objects/StarLayer.h"

using namespace cocos2d;

class BoardMembers : public CutsceneClip
{
public:
	static BoardMembers* create();

protected:
	BoardMembers();
	~BoardMembers();

private:
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

	void onDialogueShown();

	Sprite* background;

	LayerColor* dialoguePlate;
	Dialogue* dialogue;
	Label* escapeLabel;

	static const Vec2 panOffset;
};
