#include "HowtoFixContentUtils.h"

#include "ContentBrowserModule.h"
#include "AssetRegistry/AssetRegistryModule.h"


void HowtoFixContent::UI::
Folder_RegisterMenuExtender()
{
	// ContentBrowser的按钮添加比较繁琐，需要经历（调用顺序的逆序噢）
	// CB添加 [ 创建 Extender[ 配置Extension (MenuUI信息和Action逻辑) ] ] // 从左往右读就是调用，从里往外则是数据构建的顺序
	FContentBrowserModule& CB                          = FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser");
	FContentBrowserMenuExtender_SelectedPaths Extender = FContentBrowserMenuExtender_SelectedPaths::CreateStatic(&Folder_MenuExtenderGet);
	CB.GetAllPathViewContextMenuExtenders().Add(Extender);

	// CB有很多很多Extender，我根本记不下来怎么办？
}


TSharedRef<FExtender> HowtoFixContent::UI::
Folder_MenuExtenderGet(const TArray<FString>& Folders)
{
	TSharedRef<FExtender> Extender = MakeShareable(new FExtender);

	// 配置Extension
	FMenuExtensionDelegate ExtensionDelegate = FMenuExtensionDelegate::CreateLambda([Folders](FMenuBuilder& InMenuBuilder)
	{
		// Action逻辑
		FUIAction Action;
		Action.ExecuteAction.BindStatic(&Folder_SpawnFixPanel, Folders);
		FText Name = FText::FromString(TEXT("CP路径规范化"));

		// MenuUI信息
		InMenuBuilder.BeginSection("Lim_Howto", FText::FromString(TEXT("Lim Howto")));
		InMenuBuilder.AddMenuEntry(Name, Name, FSlateIcon(), Action);
		InMenuBuilder.EndSection();
	});
	
	Extender->AddMenuExtension(
		"PathContextBulkOperations",
		EExtensionHook::After,
		nullptr,
		ExtensionDelegate);
		
	return Extender;
}


void HowtoFixContent::UI::
Folder_SpawnFixPanel(TArray<FString> Folders)
{
	// 收集分析必要的信息
	TSet<FAssetData> Assets;
	for (FString Folder : Folders)
		Core::CollectAssetsByFolder(Folder, Assets);

	// 创建窗体
	TSharedRef<SWindow> Window = SNew(SWindow)
	.Title(FText::FromString(FString(TEXT("CP 路径规范 - Folder"))))
	.IsTopmostWindow(true)
	.ClientSize(FVector2D(500, 800))
	.SupportsMinimize(false)
	.SupportsMaximize(false);

	

	// 做些复杂的逻辑：遍历资产，并且把每个资产的名字垂直罗列显示
	// 垂直显示可以用SVerticalBox，他有两种添加新行的方式。我们这里会演示UI的[]包装和缩进语法和 链式编程配置属性
	TSharedRef<SVerticalBox> VerticalBox = SNew(SVerticalBox)
		// 第一种方法。在构造时可以直接添加内容，特殊语法，强烈建议不要现在就展开学习内部
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew(STextBlock)
			.Text(FText::FromString(TEXT("第 1 行")))
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew(STextBlock)
			.Text(FText::FromString(TEXT("第 2 行")))
		];
	
	for (FAssetData Asset : Assets)
	{
		const FString Name     = Asset.GetFullName();
		const FText   NameText = FText::FromString(Name);

		TSharedRef<STextBlock> Row = SNew(STextBlock)
			.Text(NameText)
			.ColorAndOpacity(FLinearColor::Red);

		// 第二种方法，对对象调用AddSlot接口，运行时动态添加，等效于上文的+ SVertical::Slot
		VerticalBox->AddSlot()
		.AutoHeight()
		.Padding(1)
		[
			Row
		];
	}
	
	
	Window->SetContent(VerticalBox);

	
	FSlateApplication::Get().AddWindow(Window);
}


void HowtoFixContent::Core::
CollectAssetsByFolder(FString Folder, TSet<FAssetData>& OutAssets)
{
	FAssetRegistryModule& ARM = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");

	TArray<FAssetData> Assets;
	ARM.Get().GetAssetsByPath(FName(Folder), Assets, true);
	for (const FAssetData& Asset : Assets)
		OutAssets.Add(Asset);
}
