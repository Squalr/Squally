#pragma once

#include "Engine/GlobalScene.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableNode;
class ClickableTextNode;
class LocalizedLabel;
class LocalizedString;
class MemoryEditingTab;
class ScrollPane;

class TutorialSelectMenu : public GlobalScene
{
public:
	static TutorialSelectMenu* getInstance();

protected:
	TutorialSelectMenu();
	virtual ~TutorialSelectMenu();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef GlobalScene super;
	
	ClickableTextNode* buildTabButton(std::string iconResource, LocalizedString* localizedString);

	cocos2d::Node* background;
	cocos2d::Sprite* window;
	LocalizedLabel* title;
	LocalizedLabel* disclaimer;
	ClickableNode* closeButton;
	ClickableTextNode* cancelButton;
	ClickableTextNode* returnButton;
	cocos2d::Node* leftPanel;
	cocos2d::Node* rightPanel;

	ClickableTextNode* memoryEditingTabButton;
	ClickableTextNode* hexEditingTabButton;
	ClickableTextNode* pointersTabButton;
	ClickableTextNode* assemblyEditingTabButton;

	MemoryEditingTab* memoryEditingTab;
	MemoryEditingTab* hexEditingTab;
	MemoryEditingTab* pointersTab;
	MemoryEditingTab* assemblyEditingTab;

	ClickableTextNode* buildTutorialButton(std::string displayName, std::string mapResource);

	static TutorialSelectMenu* instance;
};
