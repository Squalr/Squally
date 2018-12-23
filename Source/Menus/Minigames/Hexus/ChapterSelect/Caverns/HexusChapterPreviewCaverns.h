#pragma once
#include <string>

#include "Menus/Minigames/Hexus/ChapterSelect/HexusChapterPreview.h"

class HexusChapterPreviewCaverns : public HexusChapterPreview
{
public:
	static HexusChapterPreviewCaverns* create();

	static const std::string SaveKeyChapterName;

protected:
	HexusChapterPreviewCaverns();
	~HexusChapterPreviewCaverns();

private:
	void initializePositions() override;
};
