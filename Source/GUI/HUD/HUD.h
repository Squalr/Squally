#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Objects/Hackables/HackableObject.h"
#include "GUI/Menus/Dialog/DialogMenu.h"
#include "GUI/Menus/HackerMode/DataCodeMenu.h"
#include "GUI/Components/Mouse.h"

using namespace cocos2d;

class HUD : public Node
{
public:
	static HUD * create();

	Layer * hackableObjectsHud;

	void registerHackableObject(HackableObject* hackableObject);

private:
	HUD();
	~HUD();

	void onHackableEdit(EventCustom* eventArgs);
	void onEnter() override;
	void initializePositions();
	void initializeListeners();
	void onDialogOpen(EventCustom* event);

	Sprite* heart;
	Sprite* healthBarFrame;

	DataCodeMenu* dataCodeMenu;
	Node* dialogNode;
};

