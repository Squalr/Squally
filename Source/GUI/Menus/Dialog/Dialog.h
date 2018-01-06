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

class Dialog : public Node
{
public:
	static Dialog * loadDialogFromFile(std::string filePath);

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

	static Dialog * loadDialogFromJson(std::string json);
	static Dialog * create(Portrait portraitLeft, Portrait portraitRight, Speaker speaker, TextMood textMood, std::string text, std::map<std::string, Dialog*>* children);

	static Portrait stringToPortrait(std::string portraitNameString);
	static Speaker stringToSpeaker(std::string speakerString);
	static TextMood stringToTextMood(std::string textMoodString);

	std::map<MenuLabel*, Dialog*>* dialogChildren;
	std::string dialogChoice;

private:
	Dialog(Portrait portraitLeft, Portrait portraitRight, Speaker speaker, TextMood textMood, std::string text, std::map<std::string, Dialog*>* children);
	~Dialog();

	void initializePositions();
	Node* getPortraitNode(Portrait portrait, bool isRight);
	void onChooseDialog(MenuLabel* dialogMenu);

	Node* spriteLeft;
	Node* spriteRight;
	Label* dialogText;
	ClippingNode* spriteLeftClip;
	ClippingNode* spriteRightClip;
};
