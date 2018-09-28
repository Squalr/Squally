#pragma once
#include "cocos2d.h"
#include "Resources.h"

#include "Engine/UI/Controls/MenuSprite.h"
#include "Scenes/Menus/Minigames/Hexus/ChapterSelect/HexusChapterPreview.h"

using namespace cocos2d;

class HexusChapterPreviewMech : public HexusChapterPreview
{
public:
	static HexusChapterPreviewMech * create();

	static const std::string stringKeyChapterName;

protected:
	HexusChapterPreviewMech();
	~HexusChapterPreviewMech();

private:
	void initializePositions() override;
};
