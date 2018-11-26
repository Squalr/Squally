#pragma once
#include "ui/CocosGUI.h"
#include "cocos2d.h"

#include "Engine/Localization/Localization.h"
#include "Engine/SmartNode.h"
#include "Engine/UI/Controls/MenuLabel.h"

using namespace cocos2d;
using namespace cocos2d::ui;

class TextWindow : public SmartNode
{
public:
	static TextWindow * create(std::string windowTitle, Size initWindowSize, float initFontSize, Color3B initFontColor);

	void setTitle(std::string title);
	void insertText(std::string text, Color3B color);
	void setMarginSize(float newMarginSize);
	virtual void insertNewline();
	virtual void clearText();

protected:
	TextWindow(std::string windowTitle, Size initWindowSize, float initFontSize, Color3B initFontColor);
	~TextWindow();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void update(float) override;

	void setWindowColor(Color4B newWindowColor);
	void setTitleBarColor(Color4B newTitleBarColor);

	ScrollView* scrollView;
	float marginSize;

	static const Size padding;

private:
	Node* background;
	Node* titleBar;
	MenuLabel* windowTitle;
	RichText* displayedText;

	std::vector<RichElement*> displayTextElements;

	float fontSize;
	Color4B titleBarColor;
	Color4B windowColor;
	Color3B fontColor;
	Size windowSize;

	static const float titleBarHeight;
	static const Color4B defaultTitleBarColor;
	static const Color4B defaultWindowColor;
};

