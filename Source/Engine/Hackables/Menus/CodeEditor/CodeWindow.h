#pragma once
#include <set>
#include <string>
#include <vector>

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class LayerColor;
	class Sprite;

	namespace ui
	{
		class RichText;
		class RichElement;
		class RichElementText;
	}
}

class ClickableNode;
class InputText;
class LocalizedLabel;
class LocalizedString;
class ScriptEntry;
class ScrollPane;
	
struct AsmToken
{
	LocalizedString* tokenStr;
	cocos2d::Color3B color;

	AsmToken(LocalizedString* tokenStr, cocos2d::Color3B color) :
		tokenStr(tokenStr), color(color)
	{
	}
};

class CodeWindow : public SmartNode
{
public:
	static CodeWindow* create(cocos2d::Size windowSize);

	void openScript(ScriptEntry* script);
	bool hasChanges();
	void clearHasChanges();
	std::string getText();
	void focus();
	void unfocus();

protected:
	CodeWindow(cocos2d::Size windowSize);
	virtual ~CodeWindow();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef SmartNode super;

	void setWindowTitle(std::string windowTitle);
	void insertText(LocalizedString* text, cocos2d::Color3B color);
	void insertNewline();
	void clearText();
	void setText(std::string text);
	void constructTokenizedText(std::string currentText);

	cocos2d::LayerColor* background;
	cocos2d::LayerColor* titleBar;
	InputText* windowTitle;
	ClickableNode* deleteButton;
	cocos2d::Sprite* copyButtonGlow;
	ClickableNode* copyButton;
	ScrollPane* contentPane;
	cocos2d::ui::RichText* displayedText;
	InputText* editableText;
	cocos2d::ui::RichText* lineNumbers;
	cocos2d::LayerColor* deletePanel;
	LocalizedLabel* deleteLabel;
	cocos2d::LayerColor* copyPanel;
	LocalizedLabel* copyLabel;

	std::vector<std::tuple<LocalizedString*, cocos2d::Color3B>> textInfo;
	std::vector<cocos2d::ui::RichElementText*> textElements;
	std::vector<cocos2d::ui::RichElement*> lineNumberElements;

	bool hasScriptChanges;
	ScriptEntry* script;
	int currentLineNumber;
	cocos2d::Size windowSize;

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
	static const cocos2d::Size Padding;
	static const float MarginSize;
};
