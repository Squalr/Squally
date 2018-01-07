#pragma once
#include "cocos2d.h"
#include "document.h"
#include "stringbuffer.h"
#include "writer.h"
#include "Resources.h"
#include "GUI/Components/FloatingSprite.h"
#include "GUI/Components/MenuLabel.h"

using namespace cocos2d;
using namespace rapidjson;

class DialogMenu : public Node
{
public:
	static DialogMenu * loadDialogFromFile(std::string filePath);

	static const std::string DialogOpenEvent;

	struct DialogOpenArgs
	{
		DialogMenu* dialogMenu;

		DialogOpenArgs(DialogMenu* dialogMenu) : dialogMenu(dialogMenu)
		{
		}
	};

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

	static DialogMenu * loadDialogFromJson(std::string json);
	static DialogMenu * create(Portrait portraitLeft, Portrait portraitRight, Speaker speaker, TextMood textMood, std::string text, std::queue<DialogMenu*>* children);

	static Portrait stringToPortrait(std::string portraitNameString);
	static Speaker stringToSpeaker(std::string speakerString);
	static TextMood stringToTextMood(std::string textMoodString);

	std::map<MenuLabel*, DialogMenu*>* dialogChildren;
	std::string dialogChoice;

private:
	DialogMenu(Portrait portraitLeft, Portrait portraitRight, Speaker speaker, TextMood textMood, std::string text, std::queue<DialogMenu*>* children);
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
