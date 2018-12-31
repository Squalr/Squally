#pragma once
#include <set>
#include <string>
#include <vector>

#include "Engine/UI/Controls/EditableTextWindow.h"
#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class HackableCode;
class MenuLabel;
class MenuSprite;
class TextMenuSprite;
class TextWindow;

class CodeEditor : public SmartNode
{
public:
	static CodeEditor* create();

	void open(HackableCode* hackableCode);

private:
	CodeEditor();
	~CodeEditor();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void update(float) override;
	void enableAccept();
	void disableAccept();
	void compile(std::string rawText);
	void onFunctionTextUpdate(std::string text);
	void onAllocationTextUpdate(std::string text);
	void tokenizeCallback(std::string text, std::vector<EditableTextWindow::token>&);
	void onAccept(MenuSprite* menuSprite);
	void onCancel(MenuSprite* menuSprite);

	cocos2d::Sprite* codeEditorBackground;

	TextWindow* statusWindow;
	MenuLabel* codeEditorTitle;
	EditableTextWindow* functionWindow;
	EditableTextWindow* secondaryWindow;

	TextMenuSprite* cancelButton;
	TextMenuSprite* acceptButton;
	cocos2d::Node* acceptButtonGrayed;

	HackableCode* activeHackableCode;
	float compileDelay;

	static const float compileDelayMaxSeconds;
	static const float lineNumberMargin;
	static const cocos2d::Size textSize;
	static const cocos2d::Size statusSize;
	static const cocos2d::Size functionSize;
	static const cocos2d::Size secondarySize;
	static const std::string delimiters;
	static const cocos2d::Color3B defaultColor;
	static const cocos2d::Color3B subtextColor;
	static const cocos2d::Color3B headerColor;
	static const cocos2d::Color3B errorColor;
	static const cocos2d::Color3B registerColor;
	static const cocos2d::Color3B numberColor;
	static const cocos2d::Color3B commentColor;
	static const std::set<std::string> registers;
private:
	typedef SmartNode super;
};
