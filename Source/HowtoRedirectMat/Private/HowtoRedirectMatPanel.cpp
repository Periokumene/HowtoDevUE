#include "HowtoRedirectMatPanel.h"

#include "HowtoRedirectMatUtils.h"
#include "MaterialEditor/MaterialEditorInstanceConstant.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Widgets/Layout/SSeparator.h"
#include "Editor/MaterialEditor/Private/MaterialEditorInstanceDetailCustomization.h"
#include "Framework/Notifications/NotificationManager.h"
#include "Widgets/Notifications/SNotificationList.h"


void SHowtoRedirectMatPanel::
Construct(const FArguments& InArgs)
{
	MatPairHolder = NewObject<UHowtoRedirectMatPairHolder>();
	MatPairHolder->AddToRoot(); // 强制锁定，避免被垃圾回收，直到Panel析构时再解锁
	MatPairHolder->Source = InArgs._SourceMat;
	
	FakeMIC = NewObject<UMaterialInstanceConstant>();
	FakeMIC->AddToRoot();
	FakeMIC->SetParentEditorOnly(InArgs._SourceMat);
	
	ParamsEdInst = NewObject<UMaterialEditorInstanceConstant>();
	ParamsEdInst->AddToRoot();
	ParamsEdInst->SetSourceInstance(FakeMIC);
	
	
	// 创建DetailsView控件，需要通过PEM模块来创建（超常用）
	FPropertyEditorModule& PEM = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	FDetailsViewArgs DetailsViewArgs;
	DetailsViewArgs.bAllowSearch = false;
	DetailsViewArgs.NameAreaSettings = FDetailsViewArgs::HideNameArea;
	DetailsViewArgs.bAllowMultipleTopLevelObjects = true;
	ViewMatPair = PEM.CreateDetailView(DetailsViewArgs);
	ViewParams  = PEM.CreateDetailView(DetailsViewArgs);

	
	// 但是默认的Detail自动UI不够满足复杂的参数面板。引擎是通过注册 FOnGetDetailCustomizationInstance，其内部有着自定义的UI逻辑。我们可以把它偷过来给自己用. 你可以把这块注释掉，对比前后区别
	FGetShowHiddenParameters          DelegateShowHidden = FGetShowHiddenParameters::CreateLambda([](bool&){});
	FOnGetDetailCustomizationInstance DelegateGetCustom  = FOnGetDetailCustomizationInstance::CreateStatic(&FMaterialInstanceParameterDetails::MakeInstance, ParamsEdInst, DelegateShowHidden);
	ViewParams->RegisterInstancedCustomPropertyLayout(UMaterialEditorInstanceConstant::StaticClass(), DelegateGetCustom);
	
	ViewMatPair->SetObject(MatPairHolder);
	ViewParams->SetObject(ParamsEdInst);

	
	TSharedRef<SButton> ExecButton = SNew(SButton).Text(FText::FromString(TEXT(" 执行！ ")))
	.OnClicked_Lambda([this]()
	{
		// 我们用FakeMIC承接一个虚构的供用户开关的材质球（面板），这样我们就可以选择Source中哪些参数要被传递给目标。然后在直接传递到Dest
		const bool bResult = HowtoRedirectMatUtils::Exec::PassParams(FakeMIC, MatPairHolder->Dest);

		const FString Log  = bResult ? TEXT("成功啦 >~<") : TEXT("失敗了 T.T");
		FNotificationInfo Info(FText::FromString(Log));
		Info.ExpireDuration = 5.f;
		FSlateNotificationManager::Get().AddNotification(Info);
		
		return FReply::Handled();
	});

	
	// 我个人喜欢的写法，避免过于复杂的缩进对于新手来说负担太重
	TSharedRef<SVerticalBox> Box = SNew(SVerticalBox);
	Box->AddSlot().AutoHeight().Padding(1) [ ViewMatPair.ToSharedRef() ];
	Box->AddSlot().AutoHeight().Padding(2) [ SNew(SSeparator).Orientation(Orient_Horizontal) ];
	Box->AddSlot().AutoHeight().Padding(1) [ ViewParams.ToSharedRef() ];
	Box->AddSlot().AutoHeight().Padding(1).HAlign(HAlign_Right) [ ExecButton ];
	
	ChildSlot
	[
		Box
	];
}


SHowtoRedirectMatPanel::
~SHowtoRedirectMatPanel()
{
	if (MatPairHolder) MatPairHolder->RemoveFromRoot();
	if (ParamsEdInst)  ParamsEdInst->RemoveFromRoot();
	if (FakeMIC)       FakeMIC->RemoveFromRoot();
}


void SHowtoRedirectMatPanel::
Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	// TODO 每帧里检查是否替换了Source，并且更新
	SCompoundWidget::Tick(AllottedGeometry, InCurrentTime, InDeltaTime);
}
