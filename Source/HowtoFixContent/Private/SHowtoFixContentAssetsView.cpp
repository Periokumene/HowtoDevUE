#include "SHowtoFixContentAssetsView.h"

#include "HowtoFixContentAssetInfo.h"
#include "Widgets/Layout/SSpacer.h"


void SHowtoFixContentAssetsView::
Construct(const FArguments& InArgs)
{
	for (const FAssetData& Asset : InArgs._Assets)
		AddInfo(Asset);

	
	InfoListView = SNew(SAssetInfoListView)
		.ListItemsSource(&Infos)
		.OnGenerateRow(this, &SHowtoFixContentAssetsView::OnGenerateRow);
	
	ChildSlot
	[
		InfoListView.ToSharedRef()
	];
}


TSharedRef<ITableRow> SHowtoFixContentAssetsView::
OnGenerateRow(FAssetInfoSP Info, const TSharedRef<STableViewBase>& OwnerTable) const
{
	TSharedRef<SAssetInfoRow> Row = SNew(SAssetInfoRow, OwnerTable).Padding(2);
	TSharedRef<SWidget> Content = Info->GetUI();
	TSharedRef<SWidget> WrappedContent = SNew(SBorder).Padding(1) [ Content ];
	Row->SetContent(WrappedContent);
	return Row;
}


void SHowtoFixContentAssetsView::
AddInfo(FAssetData Asset)
{
	TSharedRef<FHowtoFixContentAssetInfo> Info = MakeShareable(new FHowtoFixContentAssetInfo);
	const UClass* Class = Asset.GetClass();
	if (Class->IsChildOf(UMaterial::StaticClass()))
		Info = MakeShareable(new FHowtoFixContentAssetInfo_M);
	else if (Class->IsChildOf(UTexture::StaticClass()))
		Info = MakeShareable(new FHowtoFixContentAssetInfo_Tex);
	
	Info->Asset = Asset;
	Infos.Add(Info);
}
