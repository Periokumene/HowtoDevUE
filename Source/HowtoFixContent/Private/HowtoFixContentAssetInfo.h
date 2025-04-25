#pragma once

#include "CoreMinimal.h"

struct FHowtoFixContentAssetInfo
{
	FHowtoFixContentAssetInfo() {}
	virtual ~FHowtoFixContentAssetInfo() {}
	virtual TSharedRef<SWidget> GetUI();
	FAssetData Asset;
};
