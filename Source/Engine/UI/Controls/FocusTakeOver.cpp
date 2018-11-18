#include "FocusTakeOver.h"

FocusTakeOver * FocusTakeOver::create()
{
	FocusTakeOver* instance = new FocusTakeOver();

	instance->autorelease();

	return instance;
}

FocusTakeOver::FocusTakeOver()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->hijackedNodes = std::map<Node*, std::tuple<Node*, int>>();
	this->focusBackground = LayerColor::create(Color4B::BLACK, visibleSize.width, visibleSize.height);

	this->focusBackground->setOpacity(0);

	this->addChild(this->focusBackground);
}

FocusTakeOver::~FocusTakeOver()
{
}

void FocusTakeOver::showPointer(Vec2 coords, float rotation)
{
}

void FocusTakeOver::focus(std::vector<Node*> nodes)
{
	this->unfocus(false);

	for (auto it = nodes.begin(); it != nodes.end(); it++)
	{
		Node* parent = (*it)->getParent();
		int zIndex = (*it)->getZOrder();

		this->hijackedNodes[*it] = std::tuple<Node*, int>(parent, zIndex);

		GameUtils::changeParent(*it, this, true);
	}

	this->focusBackground->runAction(FadeTo::create(0.25f, 196));
}

void FocusTakeOver::unfocus(bool fadeOut)
{
	for (auto it = this->hijackedNodes.begin(); it != this->hijackedNodes.end(); it++)
	{
		Node* node = (*it).first;
		Node* parent = std::get<0>((*it).second);
		int zIndex = std::get<1>((*it).second);

		GameUtils::changeParent(node, parent, true);
		node->setZOrder(zIndex);
	}

	this->hijackedNodes.clear();

	if (fadeOut)
	{
		this->focusBackground->runAction(FadeTo::create(0.25f, 0));
	}
}
