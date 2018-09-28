#pragma once
#include "cocos2d.h"
#include "Resources.h"

#include "Engine/UI/Controls/MenuSprite.h"
#include "Scenes/Menus/Minigames/Hexus/ChapterSelect/HexusChapterPreview.h"

using namespace cocos2d;

class HexusChapterPreviewCaverns : public HexusChapterPreview
{
public:
	static HexusChapterPreviewCaverns * create();

	static const std::string stringKeyChapterName;

protected:
	HexusChapterPreviewCaverns();
	~HexusChapterPreviewCaverns();

private:
	void initializePositions() override;
};
