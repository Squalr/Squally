#pragma once
#include <set>
#include <string>
#include <vector>

#include "Engine/Events/HackableEvents.h"
#include "Engine/GlobalHud.h"
#include "Engine/Hackables/CodeEditor/CodeWindow.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableNode;
class ClickableTextNode;
class HackableCode;
class LabelStack;
class Lexicon;
class MenuLabel;
class ScriptEntry;
class ScriptList;
class TextWindow;

class CodeEditor : public GlobalHud
{
public:
	static CodeEditor* create();

private:
	typedef SmartNode super;

	CodeEditor();
	~CodeEditor();

	void onEnter() override;
	void onExit() override;
	void initializePositions() override;
	void initializeListeners() override;
	void update(float) override;
	void open(HackableEvents::HackableObjectEditArgs* args);
	void enableAccept();
	void disableAccept();
	void buildRegisterWindow();
	void compile(std::string rawText);
	void onFunctionTextUpdate(std::string text);
	void tokenizeCallback(std::string text, std::vector<CodeWindow::token>&);
	void onScriptLoad(ScriptEntry* script);
	void onAccept();
	void onCancel();

	void setWindowColor(cocos2d::Color4B windowColor);
	void setTitleBarColor(cocos2d::Color4B titleBarColor);

	// This is an unused label that is simply kept around to steal attributes from (font size, font style, etc)
	LocalizedLabel* referenceContentLabel;

	float marginSize;

	cocos2d::Sprite* statusBackground;
	cocos2d::Sprite* rightBarBackground;
	cocos2d::Sprite* radialEye;
	cocos2d::Node* previewNode;
	cocos2d::Node* clippyNode;
	CodeWindow* functionWindow;
	LabelStack* statusWindow;
	LabelStack* registerWindow;
	ScriptList* scriptList;
	ClickableTextNode* cancelButton;
	ClickableTextNode* applyChangesButton;
	cocos2d::Node* applyChangesButtonGrayed;
	LocalizedLabel* titleLabel;
	ClickableTextNode* lexiconButton;
	Lexicon* lexicon;

	HackableCode* activeHackableCode;
	float compileDelay;

	static const cocos2d::Size Padding;
	static const float CompileDelayMaxSeconds;
	static const float LineNumberMargin;
	static const cocos2d::Size StatusSize;
	static const cocos2d::Size FunctionSize;
	static const cocos2d::Color4B SubtextColor;
	static const cocos2d::Color4B HeaderColor;
	static const cocos2d::Color4B ErrorColor;
	static const cocos2d::Color4B RegisterColor;
};
