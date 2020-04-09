#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class RadialEntry;
class LocalizedString;
class Sound;

class RadialScrollMenu : public SmartNode
{
public:
	static RadialScrollMenu* create(float radius);

	int getIndex();
	void clearItems();
	RadialEntry* addEntry(LocalizedString* labelStr, LocalizedString* lowerLabelStr, std::string iconResource, std::string backgroundResource, std::function<void()> callback);
	void toggleAll(bool disableInteraction = true, bool fadeOpacity = false, bool hideText = true);
	void enableAll();
	void focus();
	void unfocus();
	void scrollUp();
	void scrollDown();
	void scrollTo(int index);
	void setBackCallback(std::function<void()> backCallback);

protected:
	RadialScrollMenu(float radius);
	virtual ~RadialScrollMenu();
	
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef SmartNode super;
	void positionButtons();
	void goBack();

	std::vector<RadialEntry*> buttons;
	cocos2d::Sprite* arrow;
	cocos2d::Node* buttonsNode;
	Sound* indexChangeSound;
	Sound* errorSound;
	float radius;

	int currentIndex;
	bool focused;
	bool isTimelineCinematicPaused;
	
	std::function<void()> backCallback;
};
