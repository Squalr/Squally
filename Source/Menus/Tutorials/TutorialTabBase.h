#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class LocalizedLabel;
class LocalizedString;
class TutorialEntry;

class TutorialTabBase : public SmartNode
{
public:

protected:
	TutorialTabBase();
	virtual ~TutorialTabBase();

	void onEnter() override;
	void initializeListeners() override;
	void initializePositions() override;

	TutorialEntry* createEntry(std::string saveKey, TutorialEntry* prereq = nullptr);

private:
	typedef SmartNode super;
	
	LocalizedString* description = nullptr;
	LocalizedLabel* descriptionLabel = nullptr;
	cocos2d::Node* entryNode = nullptr;

	std::vector<TutorialEntry*> entries;
};
