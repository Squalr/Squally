#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

#include "Engine/SmartNode.h"
#include "Engine/Localization/Localization.h"
#include "Engine/UI/Controls/MenuLabel.h"
#include "Resources.h"

using namespace cocos2d;
using namespace cocos2d::ui;

class ScrollPane : public SmartNode
{
public:
	static ScrollPane * create(Size initPaneSize, Color4B initBackgroundColor);

	Size getPaneSize();
	Size getContentSize();
	void fitSizeToContent();
	void addChild(Node* child) override;

private:
	ScrollPane(Size initPaneSize, Color4B initBackgroundColor);
	~ScrollPane();

	void initializeListeners() override;
	void initializePositions() override;

	Size paneSize;
	Color4B backgroundColor;
	LayerColor* background;
	ScrollView* scrollView;
	
	static const Size marginSize;
};

