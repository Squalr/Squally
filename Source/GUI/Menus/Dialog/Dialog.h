#pragma once
#include "cocos2d.h"
#include "Resources.h"

using namespace cocos2d;


class Dialog : public Node
{
public:
	enum Portrait
	{
		NoPortrait,
		Player,
		Ether,
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

	static Dialog * create(Portrait portraitLeft, Portrait portraitRight, Speaker speaker, TextMood textMood, std::string text);

	void push(Dialog* dialog);
	void push(Dialog* dialog, std::string choice);

private:
	Dialog(Portrait portraitLeft, Portrait portraitRight, Speaker speaker, TextMood textMood, std::string text);
	~Dialog();

	void initializePositions();
	Sprite* getSprite(Portrait portrait);

	std::map<std::string, Dialog*>* children;

	Sprite* spriteLeft;
	Sprite* spriteRight;
	Label* dialogText;
};
