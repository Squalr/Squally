#pragma once
#include "cocos2d.h"
#include "Resources.h"

#include "Events/HexusEvents.h"
#include "Engine/UI/Controls/MenuSprite.h"
#include "Scenes/Hexus/CardData/CardList.h"
#include "Scenes/Maps/Platformer/PlatformerMap.h"

using namespace cocos2d;

class HexusOpponentItem : public Node
{
public:
	static HexusOpponentItem * create(std::string description, std::string mapFile, int index, std::function<void(HexusOpponentItem*)> onMouseOver);

protected:
	HexusOpponentItem(std::string description, std::string mapFile, int index, std::function<void(HexusOpponentItem*)> onMouseOver);
	~HexusOpponentItem();

private:
	void onTutorialClick(MenuSprite* HexusOpponentItem);
	void onTutorialMouseOver(MenuSprite* HexusOpponentItem);

	std::function<void(HexusOpponentItem*)> onMouseOverEvent;
	Sprite* frame;
};
