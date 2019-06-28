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
		class RichText;
		class RichElement;
	}
}

class InputText;
class LocalizedLabel;
class LocalizedString;
class ScrollPane;

class CodeWindow : public SmartNode
{
public:
	static CodeWindow* create(cocos2d::Size windowSize);
	
	struct token
	{
		LocalizedString* tokenStr;
		cocos2d::Color3B color;

		token(LocalizedString* tokenStr, cocos2d::Color3B color) :
			tokenStr(tokenStr), color(color)
		{
		}
	};

	void setWindowTitle(std::string windowTitle);
	void insertText(LocalizedString* text, cocos2d::Color3B color);
	void toggleHeader(bool isVisible);
	void toggleBackground(bool isVisible);
	void enableWrapByChar();
	void enableWrapByWord();
	void insertNewline();
	void clearText();
	void setTokenizationCallback(std::function<void(std::string text, std::vector<CodeWindow::token>&)> newTokenizationCallback);
	void setOnEditCallback(std::function<void(std::string text)> newOnEditCallback);
	std::string getText();
	std::string getTitle();
	void setText(std::string text);
	void focus();
	void unfocus();

private:
	typedef SmartNode super;
	CodeWindow(cocos2d::Size windowSize);
	virtual ~CodeWindow();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void update(float) override;
	void constructTokenizedText(std::string currentText);
	void rebuildText();

	cocos2d::LayerColor* background;
	cocos2d::LayerColor* titleBar;
	InputText* windowTitle;
	ScrollPane* contentPane;
	cocos2d::ui::RichText* displayedText;
	InputText* editableText;
	cocos2d::ui::RichText* lineNumbers;

	std::vector<std::tuple<LocalizedString*, cocos2d::Color3B>> textElements;
	std::vector<cocos2d::ui::RichElement*> lineNumberElements;
	std::function<void(std::string text, std::vector<CodeWindow::token>&)> tokenizationCallback;
	std::function<void(std::string text)> onEditCallback;

	int currentLineNumber;
	cocos2d::Size windowSize;
	std::string previousText;

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
	static const float MarginSize;
};
