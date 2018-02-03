#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Resources.h"
#include "Shaders/PostProcess.h"
#include "GUI/Components/MenuLabel.h"
#include "GUI/Components/MenuSprite.h"
#include "GUI/Components/MouseOverPanel.h"
#include "GUI/Components/EditableTextWindow.h"
#include "GUI/Components/TextWindow.h"
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

	void initializePositions();
	void initializeListeners();
	void update(float) override;
	void enableAccept();
	void disableAccept();
	void compile(std::string rawText);
	void onFunctionTextUpdate(std::string text);
	void onAllocationTextUpdate(std::string text);
	void tokenizeCallback(std::string text, std::vector<EditableTextWindow::token>*);
	void onAccept(MenuSprite* menuSprite);
	void onCancel(MenuSprite* menuSprite);

	Sprite* codeEditorBackground;

	TextWindow* statusWindow;
	MenuLabel* codeEditorTitle;
	EditableTextWindow* functionWindow;
	EditableTextWindow* secondaryWindow;

	MenuSprite* cancelButton;
	MenuSprite* acceptButton;
	Sprite* acceptButtonGrayed;

	HackableCode* activeHackableCode;
	float compileDelay;

	static const float compileDelayMaxSeconds;
	static const float lineNumberMargin;
	static const Size textSize;
	static const Size statusSize;
	static const Size functionSize;
	static const Size secondarySize;
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

