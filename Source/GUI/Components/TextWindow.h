#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Resources.h"
#include "GUI/Components/MenuLabel.h"
#include "Objects/Hackables/HackableObject.h"

using namespace cocos2d;
using namespace cocos2d::ui;

class TextWindow : public Node
{
public:
	static TextWindow * create(std::string windowTitle, Size initWindowSize, int initFontSize, Color3B initFontColor);

	void setTitle(std::string title);
	void insertText(std::string text, Color3B color);
	void setMarginSize(float newMarginSize);
	virtual void insertNewline();
	virtual void clearText();

protected:
	TextWindow(std::string windowTitle, Size initWindowSize, int initFontSize, Color3B initFontColor);
	~TextWindow();

	virtual void initializePositions();
	void setWindowColor(Color4B newWindowColor);
	void setTitleBarColor(Color4B newTitleBarColor);

	ScrollView* scrollView;
	float marginSize;

	static const Size padding;

private:

	void initializeListeners();
	void update(float) override;

	Node* background;
	Node* titleBar;
	MenuLabel* windowTitle;
	RichText* displayedText;

	std::vector<RichElement*>* displayTextElements;

	float fontSize;
	Color4B titleBarColor;
	Color4B windowColor;
	Color3B fontColor;
	Size windowSize;

	static const float titleBarHeight;
	static const Color4B defaultTitleBarColor;
	static const Color4B defaultWindowColor;
};

