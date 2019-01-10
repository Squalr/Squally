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
	typedef SmartNode super;

	CodeEditor();
	~CodeEditor();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void update(float) override;
	void open(HackableEvents::HackableObjectEditArgs* args);
	void enableAccept();
	void disableAccept();
	void buildRegisterWindow();
	void compile(std::string rawText);
	void onFunctionTextUpdate(std::string text);
	void onAllocationTextUpdate(std::string text);
	void tokenizeCallback(std::string text, std::vector<EditableTextWindow::token>&);
	void onAccept(ClickableNode* menuSprite);
	void onCancel(ClickableNode* menuSprite);

	cocos2d::Sprite* statusBackground;
	cocos2d::Sprite* rightBarBackground;
	EditableTextWindow* functionWindow;
	TextWindow* statusWindow;
	TextWindow* registerWindow;

	ClickableTextNode* cancelButton;
	ClickableTextNode* applyChangesButton;
	cocos2d::Node* applyChangesButtonGrayed;

	HackableCode* activeHackableCode;
	float compileDelay;

	static const float compileDelayMaxSeconds;
	static const float lineNumberMargin;
	static const cocos2d::Size statusSize;
	static const cocos2d::Size functionSize;
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
};
