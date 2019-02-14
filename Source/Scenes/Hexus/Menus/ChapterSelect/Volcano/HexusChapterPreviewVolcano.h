#pragma once

#include "Scenes/Hexus/Menus/ChapterSelect/HexusChapterPreview.h"

class HexusChapterPreviewVolcano : public HexusChapterPreview
{
public:
	static HexusChapterPreviewVolcano * create();

	static const std::string SaveKeyChapterName;

protected:
	HexusChapterPreviewVolcano();
	~HexusChapterPreviewVolcano();

private:
	typedef HexusChapterPreview super;
	void initializePositions() override;
};
