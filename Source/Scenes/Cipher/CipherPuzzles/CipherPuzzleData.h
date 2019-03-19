#pragma once
#include <map>

#include "Engine/SmartNode.h"

class CipherPuzzleData : public SmartNode
{
protected:
	CipherPuzzleData(std::map<std::string, std::string> inputsOutputsPanel);
	~CipherPuzzleData();

	void initializeListeners() override;

private:
	typedef SmartNode super;

	std::map<std::string, std::string> inputsOutputsPanel;
};
