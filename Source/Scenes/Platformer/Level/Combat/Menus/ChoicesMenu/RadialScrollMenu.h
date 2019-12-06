#pragma once

#include "Engine/SmartNode.h"

class ClickableTextNode;

class RadialScrollMenu : public SmartNode
{
public:
	static RadialScrollMenu* create(float radius);

	void clearItems();
	void addEntry(ClickableTextNode* button);

private:
	typedef SmartNode super;
	RadialScrollMenu(float radius);
	virtual ~RadialScrollMenu();

	void positionButtons();

	std::vector<ClickableTextNode*> buttons;
	cocos2d::Node* buttonsNode;
	float radius;
};
