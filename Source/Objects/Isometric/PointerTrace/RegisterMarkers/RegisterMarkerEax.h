#pragma once

#include "Objects/Isometric/PointerTrace/RegisterMarkers/RegisterMarker.h"

class RegisterMarkerEax : public RegisterMarker
{
public:
	static RegisterMarkerEax* create();

protected:
	RegisterMarkerEax();
	virtual ~RegisterMarkerEax();

	int getRegisterIndex() override;

private:
	typedef RegisterMarker super;
};
