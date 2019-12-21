#pragma once

#include "Engine/GlobalScene.h"

class ClickableTextNode;
class ScrollPane;

class DeveloperScene : public GlobalScene
{
public:
	static DeveloperScene* getInstance();

protected:
	DeveloperScene();
	~DeveloperScene();

private:
	typedef GlobalScene super;
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

	ScrollPane* scrollPane;
	std::vector<ClickableTextNode*> chapterList;

	ClickableTextNode* buildDebugButton(std::string displayName, std::string mapResource);

	static DeveloperScene* instance;
};
