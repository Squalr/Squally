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

class LocalizedLabel;
class LocalizedString;

class TextWindow : public SmartNode
{
public:
	static TextWindow* create(LocalizedString* windowTitle, cocos2d::Size initWindowSize, cocos2d::Color3B initFontColor);

	void setTitleStringReplaceVariables(std::vector<std::string> stringReplaceVariables);
	void insertText(std::string text, cocos2d::Color3B color);
	void setMarginSize(float newMarginSize);
	virtual void insertNewline();
	virtual void clearText();

protected:
	TextWindow(LocalizedString* windowTitle, cocos2d::Size initWindowSize, cocos2d::Color3B initFontColor);
	virtual ~TextWindow();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void update(float) override;

	void setWindowColor(cocos2d::Color4B newWindowColor);
	void setTitleBarColor(cocos2d::Color4B newTitleBarColor);

	cocos2d::ui::ScrollView* scrollView;
	float marginSize;
	LocalizedLabel* referenceLabel;

	static const cocos2d::Size Padding;

private:
	typedef SmartNode super;
	cocos2d::Node* background;
	cocos2d::Node* titleBar;
	LocalizedLabel* windowTitle;
	cocos2d::ui::RichText* displayedText;

	std::vector<cocos2d::ui::RichElement*> displayTextElements;

	cocos2d::Color4B titleBarColor;
	cocos2d::Color4B windowColor;
	cocos2d::Color3B fontColor;
	cocos2d::Size windowSize;

	static const float TitleBarHeight;
	static const cocos2d::Color4B DefaultTitleBarColor;
	static const cocos2d::Color4B DefaultWindowColor;
};
