#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Resources.h"
#include "Shaders/PostProcess.h"
#include "GUI/Components/MenuLabel.h"
#include "GUI/Components/MenuSprite.h"
#include "GUI/Components/MouseOverPanel.h"
#include "Objects/Hackables/HackableObject.h"
#include "Utils/HackUtils.h"
#include "Utils/StrUtils.h"

using namespace cocos2d;
using namespace cocos2d::ui;

class TextWindow : public Node
{
public:
	static TextWindow * create(std::string windowTitle);

	struct token
	{
		std::string tokenStr;
		Color3B color;

		token(std::string tokenStr, Color3B color) : tokenStr(tokenStr), color(color)
		{
		}
	};

	void setTokenizationCallback(std::function<std::vector<TextWindow::token>*(std::string text)> newTokenizationCallback);
	void setTitle(std::string title);
	void setText(std::string text);
	void focus();

private:
	TextWindow(std::string windowTitle);
	~TextWindow();

	void initializePositions();
	void initializeListeners();
	void update(float) override;
	void constructCodeRichText(std::string currentText);
	void insertLineNumber(int lineNumber);

	MenuLabel* windowTitle;
	ScrollView* scrollView;
	RichText* lineNumbers;
	TextField* editableText;
	RichText* displayedText;

	std::vector<RichElement*>* lineNumberElements;
	std::vector<RichElement*>* displayTextElements;
	std::string previousAssemblyText;

	std::function<std::vector<TextWindow::token>*(std::string text)> tokenizationCallback;

	static const float lineNumberMargin;
	static const Size textSize;

	static const Color3B defaultColor;
	static const Color3B subtextColor;
	static const Color3B headerColor;
	static const Color3B errorColor;
	static const Color3B registerColor;
	static const Color3B numberColor;
	static const Color3B commentColor;
};

