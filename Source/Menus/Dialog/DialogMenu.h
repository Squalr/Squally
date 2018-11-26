#pragma once
#include "cocos2d.h"
#include "allocators.h"
#include "encodings.h"
#include "document.h"
#include "stringbuffer.h"
#include "writer.h"

#include "Engine/Localization/Localization.h"
#include "Engine/UI/Controls/MenuLabel.h"
#include "Engine/UI/FloatingSprite.h"
#include "Events/DialogEvents.h"
#include "Resources/UIResources.h"

using namespace cocos2d;
using namespace rapidjson;

class DialogMenu : public SmartNode
{
public:
	static DialogMenu * loadDialogFromFile(std::string filePath);

protected:
	enum Portrait
	{
		NoPortrait,
		Player,
		AI,
	};

	enum Speaker
	{
		NoSpeaker,
		Left,
		Right
	};

	enum TextMood
	{
		Normal,
		Calm,
		Angry
	};

	static DialogMenu* loadDialogFromJson(std::string json);
	static DialogMenu* create(Portrait portraitLeft, Portrait portraitRight, Speaker speaker, TextMood textMood, std::string text, std::queue<std::pair<std::string, DialogMenu*>>* children);

	static Portrait stringToPortrait(std::string portraitNameString);
	static Speaker stringToSpeaker(std::string speakerString);
	static TextMood stringToTextMood(std::string textMoodString);

	std::vector<std::pair<MenuLabel*, DialogMenu*>> dialogChildren;

private:
	DialogMenu(Portrait portraitLeft, Portrait portraitRight, Speaker speaker, TextMood textMood, std::string text, std::queue<std::pair<std::string, DialogMenu*>>* children);
	~DialogMenu();

	void initializePositions();
	Node* getPortraitNode(Portrait portrait, bool isRight);
	void onChooseDialog(MenuLabel* dialogMenu);

	Sprite* dialogMenu;
	Node* spriteLeft;
	Node* spriteRight;
	Label* dialogText;
	ClippingNode* spriteLeftClip;
	ClippingNode* spriteRightClip;
	Sprite* frameLeft;
	Sprite* frameRight;
};
