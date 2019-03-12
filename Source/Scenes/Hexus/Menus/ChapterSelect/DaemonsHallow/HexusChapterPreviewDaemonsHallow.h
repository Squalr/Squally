#pragma once

#include "Scenes/Hexus/Menus/ChapterSelect/HexusChapterPreview.h"

class HexusChapterPreviewDaemonsHallow : public HexusChapterPreview
{
public:
	static HexusChapterPreviewDaemonsHallow * create();

	static const std::string SaveKeyChapterName;

protected:
	HexusChapterPreviewDaemonsHallow();
	~HexusChapterPreviewDaemonsHallow();

private:
	typedef HexusChapterPreview super;
	void initializePositions() override;
};
