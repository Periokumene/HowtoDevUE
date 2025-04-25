// Fill out your copyright notice in the Description page of Project Settings.


#include "HowtoFixContentAssetInfo.h"

#include "HowtoFixContentMisc.h"
#include "EditorWidgets/Public/SEnumCombobox.h"
#include "Widgets/Layout/SSpacer.h"

TSharedRef<SWidget> FHowtoFixContentAssetInfo::
GetUI()
{
	return SNew(STextBlock)
		.Text(FText::FromString(Asset.GetFullName()))
		.ColorAndOpacity(FLinearColor::Yellow);
}


bool FHowtoFixContentAssetInfo::
ExecMove()
{
	return false;
}


TSharedRef<SWidget> FHowtoFixContentAssetInfo_M::
GetUI()
{
	return SNew(SHorizontalBox)
	+ SHorizontalBox::Slot()
	. AutoWidth()
	. Padding(2)
	. VAlign(VAlign_Center)
	[
		SNew(STextBlock)
		.Text(FText::FromString(TEXT("MAT")))
		.Font(FCoreStyle::GetDefaultFontStyle("Bold", 12))
		.ColorAndOpacity(FLinearColor::Yellow)
	]
	+ SHorizontalBox::Slot()
	. AutoWidth()
	. VAlign(VAlign_Center)
	[
		SNew(STextBlock)
		.Font(FCoreStyle::GetDefaultFontStyle("Regular", 11))
		.Text(FText::FromName(Asset.AssetName))
	]
	+ SHorizontalBox::Slot()
	. FillWidth(1) // 如果在一堆AutoWidth里面混进一个FillWidth，它就会作为一个动态长度的填充把其他UI挤到两边。如果多个FillWidth控件的话则会按照比例系数分配
	[
		SNew(SSpacer).Size(FVector2D(1)) // 随便给长度啦，反正是FillWidth
	]
	+ SHorizontalBox::Slot()
	. AutoWidth()
	. VAlign(VAlign_Center)
	[
		// 这里我们第二次接触为UI添加事件，我们要绑定UI的状态到某些函数上，或者在UI更新的时候获得更多信息进行上下游更新
		// 如何查询确定事件（委托）的函数签名，并且绑定函数呢？问小潘，打字太累了
		SNew(SEnumComboBox, StaticEnum<EHowtoFixContent_MatCat>())
		.OnEnumSelectionChanged(this, &FHowtoFixContentAssetInfo_M::OnCatChange)
		.CurrentValue(this, &FHowtoFixContentAssetInfo_M::GetCat)
	];
}


int32 FHowtoFixContentAssetInfo_M::
GetCat() const
{
	return static_cast<int32>(MatCat);
}


void FHowtoFixContentAssetInfo_M::
OnCatChange(int32 Value, ESelectInfo::Type)
{
	MatCat = static_cast<EHowtoFixContent_MatCat>(Value);
}


bool FHowtoFixContentAssetInfo_M::
ExecMove()
{
	// Do something
	return false;
}


TSharedRef<SWidget> FHowtoFixContentAssetInfo_Tex::
GetUI()
{
	return SNew(SHorizontalBox)
	+ SHorizontalBox::Slot()
	. AutoWidth()
	. Padding(2)
	[
		SNew(STextBlock)
		.Text(FText::FromString(TEXT("TEX")))
		.Font(FCoreStyle::GetDefaultFontStyle("Bold", 12))
		.ColorAndOpacity(FLinearColor::Green)
	]
	+ SHorizontalBox::Slot()
	. AutoWidth()
	[
		SNew(STextBlock)
		.Font(FCoreStyle::GetDefaultFontStyle("Regular", 11))
		.Text(FText::FromName(Asset.AssetName))
	]
	+ SHorizontalBox::Slot()
	. FillWidth(1)
	[
		SNew(SSpacer).Size(FVector2D(1)) // 随便给长度啦，反正是FillWidth
	]
	+ SHorizontalBox::Slot()
	. AutoWidth()
	. VAlign(VAlign_Center)
	[
		// 这里我们第二次接触为UI添加事件，我们要绑定UI的状态到某些函数上，或者在UI更新的时候获得更多信息进行上下游更新
		// 如何查询确定事件（委托）的函数签名，并且绑定函数呢？问小潘，打字太累了
		SNew(SEnumComboBox, StaticEnum<EHowtoFixContent_TexCat>())
		.OnEnumSelectionChanged(this, &FHowtoFixContentAssetInfo_Tex::OnCatChange)
		.CurrentValue(this, &FHowtoFixContentAssetInfo_Tex::GetCat)
	];
}


int32 FHowtoFixContentAssetInfo_Tex::
GetCat() const
{
	return static_cast<int32>(Cat);
}


void FHowtoFixContentAssetInfo_Tex::
OnCatChange(int32 Value, ESelectInfo::Type)
{
	Cat = static_cast<EHowtoFixContent_TexCat>(Value);
}


bool FHowtoFixContentAssetInfo_Tex::ExecMove()
{
	return FHowtoFixContentAssetInfo::ExecMove();
}
