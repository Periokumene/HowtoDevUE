// Fill out your copyright notice in the Description page of Project Settings.


#include "HowtoFixContentAssetInfo.h"

TSharedRef<SWidget> FHowtoFixContentAssetInfo::
GetUI()
{
	return SNew(STextBlock)
		.Text(FText::FromString(Asset.GetFullName()))
		.ColorAndOpacity(FLinearColor::Yellow);
}
