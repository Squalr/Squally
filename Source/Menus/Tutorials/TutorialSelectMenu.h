#pragma once

#include "Engine/GlobalScene.h"

namespace cocos2d
{
	class Sprite;
}

class AssemblyEditingTab;
class ClickableNode;
class ClickableTextNode;
class HexEditingTab;
class HomeTab;
class LocalizedLabel;
class LocalizedString;
class PointersTab;
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

	enum class Tab
	{
		Home,
		MemoryEditing,
		HexEditing,
		Pointers,
		AssemblyEditing,
	};
	
	void setActiveTab(Tab tab);
	void onReturnClick();
	ClickableTextNode* buildTabButton(std::string iconResource, LocalizedString* localizedString);

	cocos2d::Node* background;
	cocos2d::Sprite* window;
	LocalizedLabel* title;
	ClickableNode* closeButton;
	ClickableTextNode* returnButton;
	cocos2d::Node* leftPanel;
	cocos2d::Node* rightPanel;

	ClickableTextNode* homeTabButton;
	ClickableTextNode* memoryEditingTabButton;
	ClickableTextNode* hexEditingTabButton;
	ClickableTextNode* pointersTabButton;
	ClickableTextNode* assemblyEditingTabButton;

	HomeTab* homeTab;
	MemoryEditingTab* memoryEditingTab;
	HexEditingTab* hexEditingTab;
	PointersTab* pointersTab;
	AssemblyEditingTab* assemblyEditingTab;

	Tab activeTab;

	static TutorialSelectMenu* instance;
};
