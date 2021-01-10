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
	virtual ~DeveloperScene();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef GlobalScene super;

	struct ChapterDebugInfo
	{
		ClickableTextNode* titleButton;
		std::vector<ClickableTextNode*> mapList;
		ScrollPane* scrollPane;

		ChapterDebugInfo(ClickableTextNode* titleButton, std::vector<ClickableTextNode*> mapList, ScrollPane* scrollPane)
			: titleButton(titleButton), mapList(mapList), scrollPane(scrollPane) { }
	};

	void selectChapter(int index);
	ScrollPane* buildScrollPane();
	ClickableTextNode* buildTitleButton(std::string displayName);
	ClickableTextNode* buildDebugButton(std::string displayName, std::string mapResource);

	std::vector<ChapterDebugInfo> chapterDebugInfoList;

	static DeveloperScene* Instance;
};
