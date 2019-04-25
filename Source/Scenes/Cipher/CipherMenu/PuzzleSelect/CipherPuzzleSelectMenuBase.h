#pragma once
#include "cocos/base/CCEventKeyboard.h"

#include "Engine/GlobalScene.h"
#include "Events/NavigationEvents.h"

namespace cocos2d
{
	class Sprite;
}

class LocalizedLabel;
class CipherPuzzlePreview;
class ClickableNode;
class ScrollPane;
class ClickableTextNode;

class CipherPuzzleSelectMenuBase : public GlobalScene
{
protected:
	CipherPuzzleSelectMenuBase(NavigationEvents::NavigateCipherPuzzleSelectArgs::Chapter chapter, std::string chapterProgressSaveKey);
	~CipherPuzzleSelectMenuBase();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void loadProgress();
	void onBackClick();
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void buildOpponentList();
	static std::string buildCipherJson(std::string rule, std::vector<std::string> inputs);

	NavigationEvents::NavigateCipherPuzzleSelectArgs::Chapter chapter;

	ScrollPane* scrollPane;
	std::vector<CipherPuzzlePreview*> chests;
	std::map<CipherPuzzlePreview*, CipherPuzzlePreview*> dependencies;

	std::string chapterProgressSaveKey;
	cocos2d::Sprite* background;
	ClickableTextNode* backButton;
	
private:
	typedef GlobalScene super;
};
