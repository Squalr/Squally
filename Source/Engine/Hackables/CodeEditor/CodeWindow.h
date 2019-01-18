#pragma once
#include <set>
#include <string>
#include <vector>

#include "cocos/base/ccTypes.h"

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class LayerColor;

	namespace ui
	{
		class UICCTextField;
		class RichText;
		class RichElement;
	}
}

class LocalizedLabel;
class LocalizedString;

class CodeWindow : public SmartNode
{
public:
	static CodeWindow* create(LocalizedString* windowTitle, cocos2d::Size initWindowSize);
	
	struct token
	{
		LocalizedString* tokenStr;
		cocos2d::Color3B color;

		token(LocalizedString* tokenStr, cocos2d::Color3B color) :
			tokenStr(tokenStr), color(color)
		{
		}
	};

	void setTitleStringReplaceVariables(LocalizedString* stringReplaceVariables);
	void setTitleStringReplaceVariables(std::vector<LocalizedString*> stringReplaceVariables);
	void insertText(LocalizedString* text, cocos2d::Color3B color);
	void setMarginSize(float newMarginSize);
	void toggleHeader(bool isVisible);
	void toggleBackground(bool isVisible);
	void enableWrapByChar();
	void enableWrapByWord();
	void insertNewline();
	void clearText();
	void setTokenizationCallback(std::function<void(std::string text, std::vector<CodeWindow::token>&)> newTokenizationCallback);
	void setOnEditCallback(std::function<void(std::string text)> newOnEditCallback);
	std::string getText();
	void setText(std::string text);
	void focus();

private:
	typedef SmartNode super;
	CodeWindow(LocalizedString* windowTitle, cocos2d::Size initWindowSize);
	virtual ~CodeWindow();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void update(float) override;
	void constructTokenizedText(std::string currentText);
	void rebuildText();

	cocos2d::LayerColor* background;
	cocos2d::LayerColor* titleBar;
	LocalizedString* windowTitle;
	cocos2d::ui::UICCTextField* editableWindowTitle;
	cocos2d::ui::RichText* displayedText;
	cocos2d::ui::UICCTextField* editableText;
	cocos2d::ui::RichText* lineNumbers;

	std::vector<std::tuple<LocalizedString*, cocos2d::Color3B>> textElements;
	std::vector<cocos2d::ui::RichElement*> lineNumberElements;
	std::function<void(std::string text, std::vector<CodeWindow::token>&)> tokenizationCallback;
	std::function<void(std::string text)> onEditCallback;

	float marginSize;
	int currentLineNumber;
	cocos2d::Size windowSize;
	std::string previousText;
	LocalizedLabel* referenceContentLabel;

	static const std::string Delimiters;
	static const std::set<std::string> Registers;
	static const cocos2d::Color3B DefaultColor;
	static const cocos2d::Color3B RegisterColor;
	static const cocos2d::Color3B NumberColor;
	static const cocos2d::Color3B CommentColor;
	static const float TitleBarHeight;
	static const cocos2d::Color4B DefaultTitleBarColor;
	static const cocos2d::Color4B DefaultWindowColor;
	static const cocos2d::Color3B LineNumberColor;
	static const cocos2d::Size Padding;
};
