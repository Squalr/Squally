#pragma once
#include <string>

#include "Menus/Hexus/ChapterSelect/HexusChapterPreview.h"

class HexusChapterPreviewCastle : public HexusChapterPreview
{
public:
	static HexusChapterPreviewCastle* create();

	static const std::string SaveKeyChapterName;

protected:
	HexusChapterPreviewCastle();
	~HexusChapterPreviewCastle();

private:
	void initializePositions() override;
};
