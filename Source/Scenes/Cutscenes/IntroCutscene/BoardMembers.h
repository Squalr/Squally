#pragma once
#include "cocos/math/Vec2.h"

#include "Engine/Cutscenes/CutsceneClip.h"

namespace cocos2d
{
	class LayerColor;
	class Sprite;
}

class DialogueLabel;
class LocalizedLabel;

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

	cocos2d::Sprite* background;

	cocos2d::LayerColor* dialoguePlate;
	DialogueLabel* dialogue;
	LocalizedLabel* escapeLabel;

	static const cocos2d::Vec2 panOffset;
};
