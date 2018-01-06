#pragma once
#include "cocos2d.h"
#include "document.h"
#include "Resources.h"
#include "GUI/Components/FloatingSprite.h"

using namespace cocos2d;
using namespace rapidjson;

class Dialog : public Node
{
public:
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

	static Dialog * loadDialogFromFile(std::string filePath);
	static Dialog * loadDialogFromJson(std::string json);
	static Dialog * create(Portrait portraitLeft, Portrait portraitRight, Speaker speaker, TextMood textMood, std::string text);

protected:
	std::map<std::string, Dialog*>* children;
	std::string dialogChoice;

private:
	Dialog(Portrait portraitLeft, Portrait portraitRight, Speaker speaker, TextMood textMood, std::string text);
	~Dialog();

	void initializePositions();
	Node* getPortraitNode(Portrait portrait, bool isRight);

	static Portrait stringToPortrait(std::string portraitNameString);
	static Speaker stringToSpeaker(std::string speakerString);
	static TextMood stringToTextMood(std::string textMoodString);

	Node* spriteLeft;
	Node* spriteRight;
	Label* dialogText;
	ClippingNode* spriteLeftClip;
	ClippingNode* spriteRightClip;
};
