#pragma once
#include <string>
#include <queue>
#include <utility>

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class ClippingNode;
	class Node;
	class Sprite;
}

class LocalizedLabel;
class MenuLabel;

class DialogMenu : public SmartNode
{
public:
	static DialogMenu* loadDialogFromFile(std::string filePath);

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
	typedef SmartNode super;
	DialogMenu(Portrait portraitLeft, Portrait portraitRight, Speaker speaker, TextMood textMood, std::string text, std::queue<std::pair<std::string, DialogMenu*>>* children);
	~DialogMenu();

	void initializePositions();
	cocos2d::Node* getPortraitNode(Portrait portrait, bool isRight);
	void onChooseDialog(MenuLabel* dialogMenu);

	cocos2d::Sprite* dialogMenu;
	cocos2d::Node* spriteLeft;
	cocos2d::Node* spriteRight;
	LocalizedLabel* dialogText;
	cocos2d::ClippingNode* spriteLeftClip;
	cocos2d::ClippingNode* spriteRightClip;
	cocos2d::Sprite* frameLeft;
	cocos2d::Sprite* frameRight;
};
