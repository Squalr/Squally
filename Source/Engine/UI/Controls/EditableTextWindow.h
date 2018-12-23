#pragma once
#include <string>
#include <vector>

#include "cocos/base/ccTypes.h"

#include "Engine/UI/Controls/TextWindow.h"

namespace cocos2d
{
	namespace ui
	{
		class UICCTextField;
		class RichText;
		class RichElement;
	}
}

class LocalizedString;

class EditableTextWindow : public TextWindow
{
public:
	static EditableTextWindow* create(LocalizedString* windowTitle, cocos2d::Size initWindowSize, cocos2d::Color3B initFontColor);

	struct token
	{
		std::string tokenStr;
		cocos2d::Color3B color;

		token(std::string tokenStr, cocos2d::Color3B color) :
			tokenStr(tokenStr), color(color)
		{
		}
	};

	void setTokenizationCallback(std::function<void(std::string text,
			std::vector<EditableTextWindow::token>*)> newTokenizationCallback);
	void setOnEditCallback(std::function<void(std::string text)> newOnEditCallback);
	std::string getText();
	void setText(std::string text);
	void insertNewline() override;
	void clearText() override;
	void focus();

private:
	EditableTextWindow(LocalizedString* windowTitle, cocos2d::Size initWindowSize, cocos2d::Color3B initFontColor);
	virtual ~EditableTextWindow();

	void update(float) override;
	void initializePositions() override;
	void initializeListeners();
	void constructTokenizedText(std::string currentText);

	cocos2d::ui::UICCTextField* editableText;
	cocos2d::ui::RichText* lineNumbers;

	int currentLineNumber;
	cocos2d::Color3B fontColor;
	cocos2d::Size windowSize;
	std::string previousText;

	std::vector<cocos2d::ui::RichElement*>* lineNumberElements;
	std::function<void(std::string text, std::vector<EditableTextWindow::token>*)> tokenizationCallback;
	std::function<void(std::string text)> onEditCallback;

	static const cocos2d::Color3B lineNumberColor;
	static const std::string StringKeyClickToEdit;
};
