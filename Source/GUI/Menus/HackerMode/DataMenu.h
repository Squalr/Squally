#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Shaders/PostProcess.h"
#include "GUI/Components/MenuSprite.h"
#include "Objects/Hackables/HackableObject.h"

using namespace cocos2d;

class DataMenu : public Node
{
public:
	static DataMenu * create();

	void open(HackableObject* hackableObject);

private:
	DataMenu();
	~DataMenu();

	void initializePositions();
	void initializeListeners();
	void onClose(MenuSprite* menuSprite);

	Sprite* dataMenuBackground;
	MenuSprite* closeButton;
	Node* rows;
};
