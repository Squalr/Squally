#pragma once

#include "Scenes/Hexus/Menus/ChapterSelect/HexusChapterPreview.h"

class HexusChapterPreviewSeaSharpCaverns : public HexusChapterPreview
{
public:
	static HexusChapterPreviewSeaSharpCaverns* create();

	static const std::string SaveKeyChapterName;

protected:
	HexusChapterPreviewSeaSharpCaverns();
	~HexusChapterPreviewSeaSharpCaverns();

private:
	typedef HexusChapterPreview super;
	void initializePositions() override;
};
