#pragma once
#include <tuple>

#include "Engine/SmartNode.h"

class CipherPuzzleData : public SmartNode
{
public:
	std::vector<std::tuple<std::string, std::string>> getInputOutputMap();

protected:
	CipherPuzzleData(std::vector<std::tuple<std::string, std::string>> inputOutputMap);
	~CipherPuzzleData();

	void initializeListeners() override;

private:
	typedef SmartNode super;

	std::vector<std::tuple<std::string, std::string>> inputOutputMap;
};
