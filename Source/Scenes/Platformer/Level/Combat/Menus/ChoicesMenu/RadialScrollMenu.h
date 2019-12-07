#pragma once

#include "Engine/SmartNode.h"

class ClickableTextNode;
class EntryContainer;
class LocalizedString;

class RadialScrollMenu : public SmartNode
{
public:
	static RadialScrollMenu* create(float radius);

	void clearItems();
	ClickableTextNode* addEntry(LocalizedString* labelStr, cocos2d::Node* iconNode, std::string backgroundResource, std::function<void()> callback);
	void disableAll(bool disableInteraction = true);
	void enableAll();
	void scrollUp();
	void scrollDown();

protected:
	RadialScrollMenu(float radius);
	virtual ~RadialScrollMenu();
	
	void initializeListeners() override;

private:
	typedef SmartNode super;
	void positionButtons();

	std::vector<EntryContainer*> buttons;
	cocos2d::Node* buttonsNode;
	float radius;

	int currentIndex;
};
