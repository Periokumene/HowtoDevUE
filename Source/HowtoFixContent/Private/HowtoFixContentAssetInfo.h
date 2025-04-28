#pragma once

#include "CoreMinimal.h"
#include "HowtoFixContentMisc.h"

// TSharedFromThis 是什么意思？
// 你删掉就会发现编译不过，提示AsShared不是成员。这是因为你使用了 Deleatge，例如:
// .OnEnumSelectionChanged(this, &FHowtoFixContentAssetInfo_M::OnMatCatChange)，这里的this需要是智能指针
// 只有 继承了TSharedFromThis<>才能获得由 this 转 智能指针SP的 特性
struct FHowtoFixContentAssetInfo : public TSharedFromThis<FHowtoFixContentAssetInfo> 
{
	FHowtoFixContentAssetInfo() {}
	virtual ~FHowtoFixContentAssetInfo() {}

	FAssetData Asset;
	virtual TSharedRef<SWidget> GetUI();
	virtual bool                ExecMove();
	virtual FString             GetDest_Folder() const;
};

struct FHowtoFixContentAssetInfo_M : public FHowtoFixContentAssetInfo
{
	EHowtoFixContent_MatCat MatCat = EHowtoFixContent_MatCat::Default;
	
	virtual TSharedRef<SWidget> GetUI() override;
	int32                       GetCat() const;
	void                        OnCatChange(int32 Value, ESelectInfo::Type);
	virtual FString             GetDest_Folder() const override;
};

struct FHowtoFixContentAssetInfo_Tex : public FHowtoFixContentAssetInfo
{
	EHowtoFixContent_TexCat Cat = EHowtoFixContent_TexCat::Default;
	
	virtual TSharedRef<SWidget> GetUI() override;
	int32                       GetCat() const;
	void                        OnCatChange(int32 Value, ESelectInfo::Type);
	virtual FString             GetDest_Folder() const override;
};