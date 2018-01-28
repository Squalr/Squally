#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Resources.h"
#include "Shaders/PostProcess.h"
#include "GUI/Components/MenuLabel.h"
#include "GUI/Components/MenuSprite.h"
#include "GUI/Components/MouseOverPanel.h"
#include "Objects/Hackables/HackableObject.h"
#include "Utils/HackUtils.h"
#include "Utils/StrUtils.h"

using namespace cocos2d;
using namespace cocos2d::ui;

class CodeEditor : public Node
{
public:
	static CodeEditor * create();

	void open(HackableCode* hackableCode);

private:
	CodeEditor();
	~CodeEditor();

	struct token
	{
		std::string tokenStr;
		Color3B color;

		token(std::string tokenStr, Color3B color) : tokenStr(tokenStr), color(color)
		{
		}
	};

	void initializePositions();
	void initializeListeners();
	void update(float) override;
	void constructRichText(std::string rawText);
	std::vector<token>* createTokens(std::string tokenStr);
	void onClose(MenuSprite* menuSprite);

	Sprite* codeEditorBackground;
	MenuSprite* closeButton;
	TextField* assemblyCodeText;
	RichText* displayText;

	std::vector<RichElement*>* displayTextElements;
	std::string previousAssemblyText;

	static const Size textSize;
	static const std::string delimiters;
	static const Color3B defaultColor;
	static const Color3B registerColor;
	static const Color3B numberColor;

	static const std::set<std::string> registers;
};

