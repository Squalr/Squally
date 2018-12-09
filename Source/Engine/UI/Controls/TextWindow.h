#pragma once
#include <string>
#include <vector>

#include "cocos/base/ccTypes.h"

#include "Engine/SmartNode.h"

class MenuLabel;

namespace cocos2d
{
	class Node;

	namespace ui
	{
		class RichElement;
		class RichText;
		class ScrollView;
	}
}

class TextWindow : public SmartNode
{
public:
	static TextWindow * create(std::string windowTitle, cocos2d::Size initWindowSize, float initFontSize,
			cocos2d::Color3B initFontColor);

	void setTitle(std::string title);
	void insertText(std::string text, cocos2d::Color3B color);
	void setMarginSize(float newMarginSize);
	virtual void insertNewline();
	virtual void clearText();

protected:
	TextWindow(std::string windowTitle, cocos2d::Size initWindowSize, float initFontSize,
			cocos2d::Color3B initFontColor);
	virtual ~TextWindow();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void update(float) override;

	void setWindowColor(cocos2d::Color4B newWindowColor);
	void setTitleBarColor(cocos2d::Color4B newTitleBarColor);

	cocos2d::ui::ScrollView* scrollView;
	float marginSize;

	static const cocos2d::Size padding;

private:
	cocos2d::Node* background;
	cocos2d::Node* titleBar;
	MenuLabel* windowTitle;
	cocos2d::ui::RichText* displayedText;

	std::vector<cocos2d::ui::RichElement*> displayTextElements;

	float fontSize;
	cocos2d::Color4B titleBarColor;
	cocos2d::Color4B windowColor;
	cocos2d::Color3B fontColor;
	cocos2d::Size windowSize;

	static const float titleBarHeight;
	static const cocos2d::Color4B defaultTitleBarColor;
	static const cocos2d::Color4B defaultWindowColor;
};

