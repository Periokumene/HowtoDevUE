// Fill out your copyright notice in the Description page of Project Settings.


#include "HowtoFixContentAssetInfo.h"

TSharedRef<SWidget> FHowtoFixContentAssetInfo::
GetUI()
{
	return SNew(STextBlock)
		.Text(FText::FromString(Asset.GetFullName()))
		.ColorAndOpacity(FLinearColor::Yellow);
}



TSharedRef<SWidget> FHowtoFixContentAssetInfo_M::GetUI()
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
	];
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
	];
}
