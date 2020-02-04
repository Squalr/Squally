#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableTextNode;
class LocalizedString;

class RadialScrollMenu : public SmartNode
{
public:
	static RadialScrollMenu* create(float radius);

	void clearItems();
	ClickableTextNode* addEntry(LocalizedString* labelStr, cocos2d::Node* iconNode, std::string backgroundResource, std::function<void()> callback);
	void toggleAll(bool disableInteraction = true, bool fadeOpacity = false, bool hideText = true);
	void enableAll();
	void focus();
	void unfocus();
	void scrollUp();
	void scrollDown();
	void scrollTo(int index);
	void setBackCallback(std::function<void()> backCallback);

protected:
	RadialScrollMenu(float radius);
	virtual ~RadialScrollMenu();
	
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef SmartNode super;
	void positionButtons();
	void goBack();

	std::vector<ClickableTextNode*> buttons;
	cocos2d::Sprite* arrow;
	cocos2d::Node* buttonsNode;
	float radius;

	int currentIndex;
	bool focused;
	std::function<void()> backCallback;
};
