#pragma once
#include <string>

#include "Menus/Minigames/Hexus/ChapterSelect/HexusChapterPreview.h"

class HexusChapterPreviewIceCaps : public HexusChapterPreview
{
public:
	static HexusChapterPreviewIceCaps* create();

	static const std::string SaveKeyChapterName;

protected:
	HexusChapterPreviewIceCaps();
	~HexusChapterPreviewIceCaps();

private:
	void initializePositions() override;
};
