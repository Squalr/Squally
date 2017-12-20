#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "GUI/Components/Mouse.h"
#include "GUI/Components/MenuSprite.h"
#include "Level/Level.h"
#include "Utils/Utils.h"

using namespace cocos2d;

class TutorialItem : public Node
{
public:
	static TutorialItem * create(std::string description, std::string mapFile, Vec2 position);

	std::string tutorialDescription;
	std::string tutorialMapFile;

protected:
	TutorialItem(std::string description, std::string mapFile, Vec2 position);
	~TutorialItem();

private:
	void onEnter() override;
	void OnTutorialClick(MenuSprite* tutorialItem);

	std::function<void(TutorialItem*)> onMouseOverEvent;

	Mouse* mouse;
	Label* description;
	MenuSprite* sprite;
};

