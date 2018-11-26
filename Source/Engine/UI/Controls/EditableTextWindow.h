#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

#include "Engine/Localization/Localization.h"
#include "Engine/UI/Controls/TextWindow.h"

using namespace cocos2d;
using namespace cocos2d::ui;

class EditableTextWindow : public TextWindow
{
public:
	static EditableTextWindow * create(std::string windowTitle, Size initWindowSize, int initFontSize, Color3B initFontColor);

	struct token
	{
		std::string tokenStr;
		Color3B color;

		token(std::string tokenStr, Color3B color) : tokenStr(tokenStr), color(color)
		{
		}
	};

	void setTokenizationCallback(std::function<void(std::string text, std::vector<EditableTextWindow::token>*)> newTokenizationCallback);
	void setOnEditCallback(std::function<void(std::string text)> newOnEditCallback);
	std::string getText();
	void setText(std::string text);
	void insertNewline() override;
	void clearText() override;
	void focus();

private:
	EditableTextWindow(std::string windowTitle, Size initWindowSize, int initFontSize, Color3B initFontColor);
	~EditableTextWindow();

	void update(float) override;
	void initializePositions() override;
	void initializeListeners();
	void constructTokenizedText(std::string currentText);

	UICCTextField* editableText;
	RichText* lineNumbers;

	int currentLineNumber;
	float fontSize;
	Color3B fontColor;
	Size windowSize;
	std::string previousText;

	std::vector<RichElement*>* lineNumberElements;
	std::function<void(std::string text, std::vector<EditableTextWindow::token>*)> tokenizationCallback;
	std::function<void(std::string text)> onEditCallback;

	static const Color3B lineNumberColor;
	static const std::string StringKeyClickToEdit;
};
