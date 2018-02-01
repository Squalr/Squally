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
	void enableAccept();
	void disableAccept();
	void compile(std::string rawText);
	void constructCodeRichText(std::string rawText);
	std::vector<token>* createTokens(std::string tokenStr);
	void onAccept(MenuSprite* menuSprite);
	void onCancel(MenuSprite* menuSprite);

	HackableCode* activeHackableCode;

	Sprite* codeEditorBackground;
	ScrollView* codeEditorScrollView;
	TextField* assemblyCodeText;
	RichText* lineNumbers;
	RichText* assemblyCodeRichText;
	MenuSprite* cancelButton;
	MenuSprite* acceptButton;
	Sprite* acceptButtonGrayed;
	MenuLabel* codeEditorTitle;

	Sprite* allocEditorBackground;
	MenuLabel* allocEditorTitle;

	Sprite* outputBackground;
	MenuLabel* outputTitle;
	ScrollView* outputScrollView;
	RichText* outputText;

	float compileDelay;
	std::vector<RichElement*>* lineNumberElements;
	std::vector<RichElement*>* displayTextElements;
	std::vector<RichElement*>* outputTextElements;
	std::string previousAssemblyText;

	static const float compileDelayMaxSeconds;
	static const float lineNumberMargin;
	static const Size textSize;
	static const std::string delimiters;
	static const Color3B defaultColor;
	static const Color3B subtextColor;
	static const Color3B headerColor;
	static const Color3B errorColor;
	static const Color3B registerColor;
	static const Color3B numberColor;
	static const Color3B commentColor;

	static const std::set<std::string> registers;
};

