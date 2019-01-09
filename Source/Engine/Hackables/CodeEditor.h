#pragma once
#include <set>
#include <string>
#include <vector>

#include "Engine/Events/HackableEvents.h"
#include "Engine/GlobalHud.h"
#include "Engine/UI/Controls/Text/EditableTextWindow.h"

namespace cocos2d
{
	class Sprite;
}

class HackableCode;
class MenuLabel;
class ClickableNode;
class ClickableTextNode;
class TextWindow;

class CodeEditor : public GlobalHud
{
public:
	static void registerGlobalNode();

private:
	CodeEditor();
	~CodeEditor();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void update(float) override;
	void open(HackableEvents::HackableObjectEditArgs* args);
	void enableAccept();
	void disableAccept();
	void compile(std::string rawText);
	void onFunctionTextUpdate(std::string text);
	void onAllocationTextUpdate(std::string text);
	void tokenizeCallback(std::string text, std::vector<EditableTextWindow::token>&);
	void onAccept(ClickableNode* menuSprite);
	void onCancel(ClickableNode* menuSprite);

	cocos2d::Sprite* codeEditorBackground;

	TextWindow* statusWindow;
	MenuLabel* codeEditorTitle;
	EditableTextWindow* functionWindow;
	EditableTextWindow* secondaryWindow;

	ClickableTextNode* cancelButton;
	ClickableTextNode* acceptButton;
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
	static CodeEditor* instance;
private:
	typedef SmartNode super;
};
