#pragma once

#include "Engine/SmartNode.h"

class ClickableTextNode;
class LocalizedString;

class RadialScrollMenu : public SmartNode
{
public:
	static RadialScrollMenu* create(float radius);

	void clearItems();
	ClickableTextNode* addEntry(LocalizedString* labelStr, cocos2d::Node* iconNode, std::string backgroundResource, std::function<void()> callback);
	void disableAll();
	void enableAll();

protected:
	RadialScrollMenu(float radius);
	virtual ~RadialScrollMenu();

private:
	typedef SmartNode super;
	void positionButtons();

	std::vector<ClickableTextNode*> buttons;
	cocos2d::Node* buttonsNode;
	float radius;
};
