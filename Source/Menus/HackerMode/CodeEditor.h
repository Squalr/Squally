#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

#include "Engine/Localization/Localization.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Hackables/HackableObject.h"
#include "Engine/Utils/HackUtils.h"
#include "Engine/Utils/StrUtils.h"
#include "Engine/UI/Controls/EditableTextWindow.h"
#include "Engine/UI/Controls/MenuLabel.h"
#include "Engine/UI/Controls/MenuSprite.h"
#include "Engine/UI/Controls/MouseOverPanel.h"
#include "Engine/UI/Controls/TextMenuSprite.h"
#include "Engine/UI/Controls/TextWindow.h"
#include "Engine/UI/HUD/Hud.h"
#include "Resources/UIResources.h"

using namespace cocos2d;
using namespace cocos2d::ui;

class CodeEditor : public Hud
{
public:
	static CodeEditor * create();

	void open(HackableCode* hackableCode);

private:
	CodeEditor();
	~CodeEditor();

	void initializePositions() override;
	void initializeListeners() override;
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

	TextMenuSprite* cancelButton;
	TextMenuSprite* acceptButton;
	Node* acceptButtonGrayed;

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

	static const std::string StringKeyAccept;
	static const std::string StringKeyCancel;
	static const std::string StringKeyTitle;
	static const std::string StringKeyStatus;
	static const std::string StringKeyCodeEditor;
	static const std::string StringKeyAllocationEditor;
};

