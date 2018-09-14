#pragma once
#include "cocos2d.h"

#include "Engine/Hackables/HackableObject.h"

using namespace cocos2d;

class Chest : public Node
{
public:
	static Chest * create(Node* contentNode);

	virtual void open();
	virtual void close();

protected:
	Chest(Node* contentNode);
	~Chest();

	Node* content;
	Node* chestOpen;
	Node* chestClosed;

};
