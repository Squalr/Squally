#pragma once

#include "Engine/GlobalScene.h"

class ClickableTextNode;
class ScrollPane;

class DebugScene : public GlobalScene
{
public:
	static DebugScene* getInstance();

protected:
	DebugScene();
	~DebugScene();

private:
	typedef GlobalScene super;
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

	ScrollPane* scrollPane;
	std::vector<ClickableTextNode*> chapterList;

	ClickableTextNode* buildDebugButton(std::string mapResource, std::vector<std::string> mapArgs = { });

	static DebugScene* instance;
};
