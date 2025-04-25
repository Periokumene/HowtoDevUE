#include "HowtoRedirectMatUtils.h"

#include "ContentBrowserModule.h"
#include "Editor.h"
#include "HowtoRedirectMatPanel.h"
#include "MaterialEditor/DEditorParameterValue.h"
#include "MaterialEditor/MaterialEditorInstanceConstant.h"
#include "Materials/MaterialInstanceConstant.h"



void HowtoRedirectMatUtils::UI::
RegisterOption()
{
	FContentBrowserMenuExtender_SelectedAssets Delegate = UI::CreateExtenderDelegate();
	FContentBrowserModule& CB = FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser");
	CB.GetAllAssetViewContextMenuExtenders().Add(Delegate);
}


FContentBrowserMenuExtender_SelectedAssets HowtoRedirectMatUtils::UI::
CreateExtenderDelegate()
{
	// 必要知识:: Delegate的创建/绑定方式
	auto Delegate = FContentBrowserMenuExtender_SelectedAssets::CreateLambda([](const TArray<FAssetData>& Assets)
	{
		TSharedRef<FExtender> Extender = MakeShareable(new FExtender);
		if (Assets.Num() != 1)                                                return Extender;
		if (Assets[0].GetClass() != UMaterialInstanceConstant::StaticClass()) return Extender; // 必要知识 StaticClass
		
		Extender->AddMenuExtension(
			"AssetContextExploreMenuOptions",
			EExtensionHook::After,
			nullptr,
			FMenuExtensionDelegate::CreateStatic(&HowtoRedirectMatUtils::UI::CreateExtensionForMI, Assets[0]));
		return Extender;
	});
	return Delegate;
}


void HowtoRedirectMatUtils::UI::
CreateExtensionForMI(FMenuBuilder& InMenuBuilder, FAssetData Asset)
{
	FUIAction Action;
	Action.ExecuteAction.BindStatic(&HowtoRedirectMatUtils::UI::SpawnRedirectWindow, Cast<UMaterialInstanceConstant>(Asset.GetAsset()));
	
	InMenuBuilder.AddMenuEntry(
		FText::FromString(TEXT("重定向母材质")),
		FText::FromString(TEXT("重定向母材质")),
		FSlateIcon(),
		Action);
}


void HowtoRedirectMatUtils::UI::
SpawnRedirectWindow(UMaterialInstanceConstant* Mat)
{
	TSharedRef<SWindow> Window = SNew(SWindow)
	.Title(FText::FromString(FString(TEXT("重定向材质喵"))))
	.IsTopmostWindow(true)
	.ClientSize(FVector2D(500, 800))
	.SupportsMinimize(false)
	.SupportsMaximize(false);


	TSharedRef<SHowtoRedirectMatPanel> Panel = SNew(SHowtoRedirectMatPanel).SourceMat(Mat);
	Window->SetContent(Panel);
	FSlateApplication::Get().AddWindow(Window);
}


bool HowtoRedirectMatUtils::Exec::
PassParams(UMaterialInstanceConstant* Source, UMaterialInstanceConstant* Dest)
{
	if (!ensure(Source && Dest))      return false;
	if (!ensure(Dest->GetMaterial())) return false;

	
	UMaterialEditorInstanceConstant* EdSource = NewObject<UMaterialEditorInstanceConstant>();
	UMaterialEditorInstanceConstant* EdDest   = NewObject<UMaterialEditorInstanceConstant>();
	EdSource->SetSourceInstance(Source);
	EdDest  ->SetSourceInstance(Dest);

	TSet<UDEditorParameterValue*> CopyValues;
	for (const auto& Group : EdSource->ParameterGroups)
	if  (Group.GroupName == "Global")
	for (UDEditorParameterValue* Value : Group.Parameters)
	if  (Value->bOverride)
	{
		CopyValues.Add(Value);
	}
	

	bool bCopyHappen = false;
	for (auto& Group : EdDest->ParameterGroups)
	if  (Group.GroupName == "Global")
	for (int32 i = 0; i < Group.Parameters.Num(); ++i)
	{
		UDEditorParameterValue* Value = Group.Parameters[i];
		for (const auto& WishCopyValue : CopyValues)
		if  (WishCopyValue->ParameterInfo.Name == Value->ParameterInfo.Name)
		if  (WishCopyValue->GetClass()         == Value->GetClass())
		{
			UDEditorParameterValue* FakeValue = NewObject<UDEditorParameterValue>(EdDest, WishCopyValue->GetClass(), NAME_None, RF_NoFlags, WishCopyValue);
			Group.Parameters[i] = FakeValue;
			bCopyHappen = true;
			break;
		}
	}


	if (bCopyHappen) EdDest->CopyToSourceInstance();
	return true;
}
