#pragma once

#include "Engine/GlobalScene.h"

class ClickableTextNode;
class LocalizedLabel;
class ScrollPane;

class TutorialSelectMenu : public GlobalScene
{
public:
	static TutorialSelectMenu* getInstance();

protected:
	TutorialSelectMenu();
	~TutorialSelectMenu();

private:
	typedef GlobalScene super;
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

	LocalizedLabel* title;
	LocalizedLabel* disclaimer;
	ScrollPane* scrollPane;
	std::vector<ClickableTextNode*> chapterList;

	ClickableTextNode* buildTutorialButton(std::string displayName, std::string mapResource);

	static TutorialSelectMenu* instance;
};
