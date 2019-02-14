#pragma once

#include "Scenes/Hexus/Menus/ChapterSelect/HexusChapterPreview.h"

class HexusChapterPreviewCaverns : public HexusChapterPreview
{
public:
	static HexusChapterPreviewCaverns* create();

	static const std::string SaveKeyChapterName;

protected:
	HexusChapterPreviewCaverns();
	~HexusChapterPreviewCaverns();

private:
	typedef HexusChapterPreview super;
	void initializePositions() override;
};
