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

	cocos2d::Node* background = nullptr;
	cocos2d::Sprite* window = nullptr;
	LocalizedLabel* title = nullptr;
	ClickableNode* closeButton = nullptr;
	ClickableTextNode* returnButton = nullptr;
	cocos2d::Node* leftPanel = nullptr;
	cocos2d::Node* rightPanel = nullptr;

	ClickableTextNode* homeTabButton = nullptr;
	ClickableTextNode* memoryEditingTabButton = nullptr;
	ClickableTextNode* hexEditingTabButton = nullptr;
	ClickableTextNode* pointersTabButton = nullptr;
	ClickableTextNode* assemblyEditingTabButton = nullptr;

	HomeTab* homeTab = nullptr;
	MemoryEditingTab* memoryEditingTab = nullptr;
	HexEditingTab* hexEditingTab = nullptr;
	PointersTab* pointersTab = nullptr;
	AssemblyEditingTab* assemblyEditingTab = nullptr;

	Tab activeTab = Tab::Home;

	static TutorialSelectMenu* instance;
};
