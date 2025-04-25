#pragma once

#include "CoreMinimal.h"

struct FHowtoFixContentAssetInfo
{
	FHowtoFixContentAssetInfo() {}
	virtual ~FHowtoFixContentAssetInfo() {}
	virtual TSharedRef<SWidget> GetUI();
	FAssetData Asset;
};


struct FHowtoFixContentAssetInfo_M : public FHowtoFixContentAssetInfo
{
	virtual TSharedRef<SWidget> GetUI() override;
};

struct FHowtoFixContentAssetInfo_Tex : public FHowtoFixContentAssetInfo
{
	virtual TSharedRef<SWidget> GetUI() override;
};