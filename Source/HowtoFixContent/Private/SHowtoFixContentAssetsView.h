#pragma once

#include "CoreMinimal.h"


struct FHowtoFixContentAssetInfo;



// SLATE_BEGIN_ARGS... 这块代码是 Slate 必须的代码块
// 我强烈建议这次就先别关注宏展开是什么，为什么要固定写一个Construct函数被谁调的问题，因为这些现在马上去看会很困难，引入大量新概念
// 结论：
// 你可以通过SLATE宏去快速的声明一系列的参数。这些参数将会自动被打包进FArguemnts中，并获得委托、链式编程等特性，方便开发者灵活快速修改要暴露的参数
// 我们使用 SNew创建UI，内部会调用Construct去构造，并且自动初始化一个InArgs，支持以链式编程的方式去修改参数包


// SListView<XXX>是引擎提供的列表UI模板类
// 它可以绑定到一个 TSharedRef<XXX>的数组上, 为每一个成员 生成 STableRow<XXX>的UI（你可以在Row里面塞任何东西，详见OnGenerateRow)
typedef TSharedRef<FHowtoFixContentAssetInfo> FAssetInfoSP;
typedef SListView<FAssetInfoSP>               SAssetInfoListView;
typedef STableRow<FAssetInfoSP>               SAssetInfoRow;



class SHowtoFixContentAssetsView : public SCompoundWidget
{
	SLATE_BEGIN_ARGS(SHowtoFixContentAssetsView){}
		SLATE_ARGUMENT(TSet<FAssetData>, Assets)
	SLATE_END_ARGS()
	void Construct(const FArguments& InArgs);
	TSharedRef<ITableRow> OnGenerateRow(FAssetInfoSP Info, const TSharedRef<STableViewBase>& OwnerTable) const;
	
	
private:
	void AddInfo(FAssetData Asset);
	TArray<FAssetInfoSP>           Infos;
	TSharedPtr<SAssetInfoListView> InfoListView;
};
