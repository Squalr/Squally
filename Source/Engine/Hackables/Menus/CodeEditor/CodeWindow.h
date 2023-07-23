#pragma once
#include <set>
#include <string>
#include <vector>

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class LayerColor;
	class Sprite;
}

class ClickableNode;
class InputText;
class LocalizedLabel;
class LocalizedString;
class RichText;
class RichElement;
class RichElementText;
class ScriptEntry;
class ScrollPane;
	
struct AsmToken
{
	LocalizedString* tokenStr = nullptr;
	cocos2d::Color3B color;

	AsmToken(LocalizedString* tokenStr, cocos2d::Color3B color) :
		tokenStr(tokenStr), color(color)
	{
	}
};

class CodeWindow : public SmartNode
{
public:
	static CodeWindow* create(cocos2d::CSize windowSize);

	void openScript(ScriptEntry* script);
	bool hasChanges();
	void clearHasChanges();
	std::string getText();
	void focus();
	void unfocus();

protected:
	CodeWindow(cocos2d::CSize windowSize);
	virtual ~CodeWindow();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef SmartNode super;

	void setWindowTitle(LocalizedString* text);
	void insertText(LocalizedString* text, cocos2d::Color3B color);
	void insertNewline();
	void clearText();
	void setText(std::string text);
	void constructTokenizedText(std::string currentText);

	cocos2d::LayerColor* background = nullptr;
	cocos2d::LayerColor* titleBar = nullptr;
	InputText* windowTitle = nullptr;
	LocalizedLabel* readOnlyWindowTitle = nullptr;
	ClickableNode* deleteButton = nullptr;
	cocos2d::Sprite* copyButtonGlow = nullptr;
	ClickableNode* copyButton = nullptr;
	ScrollPane* contentPane = nullptr;
	RichText* displayedText = nullptr;
	InputText* editableText = nullptr;
	RichText* lineNumbers = nullptr;
	cocos2d::LayerColor* deletePanel = nullptr;
	LocalizedLabel* deleteLabel = nullptr;
	cocos2d::LayerColor* copyPanel = nullptr;
	LocalizedLabel* copyLabel = nullptr;

	std::vector<std::tuple<LocalizedString*, cocos2d::Color3B>> textInfo;
	std::vector<RichElementText*> textElements;
	std::vector<RichElement*> lineNumberElements;

	bool hasScriptChanges = false;
	ScriptEntry* script = nullptr;
	int currentLineNumber = 1;
	cocos2d::CSize windowSize;

	static const std::string Delimiters;
	static const std::set<std::string> Registers;
	static const cocos2d::Color3B DefaultColor;
	static const cocos2d::Color3B RegisterColor;
	static const cocos2d::Color3B NumberColor;
	static const cocos2d::Color3B CommentColor;
	static const float TitleBarHeight;
	static const cocos2d::Color4B DefaultTitleBarColor;
	static const cocos2d::Color4B DefaultWindowColor;
	static const cocos2d::Color4B ReadonlyWindowColor;
	static const cocos2d::Color3B LineNumberColor;
	static const cocos2d::CSize Padding;
	static const float MarginSize;
};
