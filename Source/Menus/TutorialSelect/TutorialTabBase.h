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

	TutorialEntry* createEntry();

private:
	typedef SmartNode super;
	
	LocalizedString* description;
	LocalizedLabel* descriptionLabel;
	cocos2d::Node* entryNode;

	std::vector<TutorialEntry*> entries;
};
