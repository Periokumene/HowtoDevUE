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
	TSharedRef<SAssetInfoRow> Row = SNew(SAssetInfoRow, OwnerTable);
	TSharedRef<SWidget> Content = Info->GetUI();
	Row->SetContent(Content);
	return Row;
}


void SHowtoFixContentAssetsView::
AddInfo(FAssetData Asset)
{
	TSharedRef<FHowtoFixContentAssetInfo> Info = MakeShareable(new FHowtoFixContentAssetInfo);
	Info->Asset = Asset;
	Infos.Add(Info);
}
