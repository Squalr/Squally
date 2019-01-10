#pragma once
#include <vector>

#include "cocos/base/ccTypes.h"

#include "Engine/SmartNode.h"

class MenuLabel;

namespace cocos2d
{
	class LayerColor;
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
	static TextWindow* create(LocalizedString* windowTitle, LocalizedLabel* referenceContentLabel, cocos2d::Size windowSize, cocos2d::Color3B fontColor);

	void setTitleStringReplaceVariables(LocalizedString* stringReplaceVariables);
	void setTitleStringReplaceVariables(std::vector<LocalizedString*> stringReplaceVariables);
	void insertText(LocalizedString* text, cocos2d::Color3B color);
	void setMarginSize(float newMarginSize);
	void toggleHeader(bool isVisible);
	void toggleBackground(bool isVisible);
	virtual void insertNewline();
	virtual void clearText();

protected:
	TextWindow(LocalizedString* windowTitle, LocalizedLabel* referenceContentLabel, cocos2d::Size windowSize, cocos2d::Color3B fontColor);
	virtual ~TextWindow();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

	void setWindowColor(cocos2d::Color4B windowColor);
	void setTitleBarColor(cocos2d::Color4B titleBarColor);

	// This is an unused label that is simply kept around to steal attributes from (font size, font style, etc)
	LocalizedLabel* referenceContentLabel;

	cocos2d::ui::ScrollView* scrollView;
	float marginSize;

	static const cocos2d::Size Padding;

private:
	typedef SmartNode super;
	void rebuildText();

	cocos2d::LayerColor* background;
	cocos2d::LayerColor* titleBar;
	LocalizedLabel* windowTitle;
	cocos2d::ui::RichText* displayedText;
	cocos2d::Color3B fontColor;

	std::vector<std::tuple<LocalizedString*, cocos2d::Color3B>> textElements;

	static const float TitleBarHeight;
	static const cocos2d::Color4B DefaultTitleBarColor;
	static const cocos2d::Color4B DefaultWindowColor;
};
