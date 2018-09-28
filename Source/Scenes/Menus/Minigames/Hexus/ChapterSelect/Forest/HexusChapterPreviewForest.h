#pragma once
#include "cocos2d.h"
#include "Resources.h"

#include "Engine/UI/Controls/MenuSprite.h"
#include "Scenes/Menus/Minigames/Hexus/ChapterSelect/HexusChapterPreview.h"

using namespace cocos2d;

class HexusChapterPreviewForest : public HexusChapterPreview
{
public:
	static HexusChapterPreviewForest * create();

	static const std::string stringKeyChapterName;

protected:
	HexusChapterPreviewForest();
	~HexusChapterPreviewForest();

private:
	void initializePositions() override;
};
