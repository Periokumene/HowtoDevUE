#include "SHowtoFixContentAssetsView.h"

#include "Widgets/Layout/SSpacer.h"


void SHowtoFixContentAssetsView::
Construct(const FArguments& InArgs)
{
	for (const FAssetData& Asset : InArgs._Assets)
		AddInfo(Asset);

	
	TSharedRef<SVerticalBox> VBox = SNew(SVerticalBox);
	for (const FAssetData& Asset : Assets)
	{
		VBox->AddSlot()
		. AutoHeight()
		. Padding(1)
		[
			SNew(STextBlock)
			.ColorAndOpacity(FLinearColor::Yellow)
			.Text(FText::FromString(Asset.GetFullName()))
		];
	}

	
	ChildSlot
	[
		VBox
	];
}





void SHowtoFixContentAssetsView::
AddInfo(FAssetData Asset)
{
	Assets.Add(Asset);
}
