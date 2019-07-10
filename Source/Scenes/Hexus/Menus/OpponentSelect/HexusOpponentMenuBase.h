#pragma once

#include "Engine/GlobalScene.h"

namespace cocos2d
{
	class Sprite;
}

class LocalizedLabel;
class HexusOpponentPreview;
class ClickableNode;
class ScrollPane;
class ClickableTextNode;

class HexusOpponentMenuBase : public GlobalScene
{
protected:
	HexusOpponentMenuBase(std::string chapterProgressSaveKey);
	~HexusOpponentMenuBase();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void loadProgress();
	void onBackClick();
	void onDeckManagementClick();
	void onShopClick();
	void onMouseOver(HexusOpponentPreview* opponent);
	void buildOpponentList();

	ScrollPane* scrollPane;
	std::vector<HexusOpponentPreview*> opponents;
	std::map<HexusOpponentPreview*, HexusOpponentPreview*> dependencies;

	std::string chapterProgressSaveKey;
	cocos2d::Sprite* background;
	ClickableTextNode* deckManagementButton;
	ClickableTextNode* shopButton;
	LocalizedLabel* opponentSelectLabel;
	ClickableTextNode* backButton;

private:
	typedef GlobalScene super;
};
