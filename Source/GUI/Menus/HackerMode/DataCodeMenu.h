#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "GUI/Components//MenuSprite.h"

using namespace cocos2d;

class DataCodeMenu : public Node
{
public:
	static DataCodeMenu * create();

	void activate();

private:
	DataCodeMenu();
	~DataCodeMenu();

	void initializePositions();
	void initializeListeners();
	void onClose(MenuSprite* menuSprite);

	Sprite* menuBackground;
	MenuSprite* closeButton;
};

