#pragma once

#include "CoreMinimal.h"
#include "HowtoRedirectMatPanel.generated.h"


class UMaterialEditorInstanceConstant;
class UMaterialInstanceConstant;



// 必要知识：UObject, UProperty，如何使用UObject去快速创建一个细节面板
UCLASS()
class UHowtoRedirectMatPairHolder : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category="From", DisplayName="目标材质")
	UMaterialInstanceConstant* Source = nullptr;

	UPROPERTY(EditAnywhere, Category="To", DisplayName="目标材质")
	UMaterialInstanceConstant* Dest = nullptr;
};




class SHowtoRedirectMatPanel : public SCompoundWidget
{
	SLATE_BEGIN_ARGS(SHowtoRedirectMatPanel){}
		SLATE_ARGUMENT(UMaterialInstanceConstant*, SourceMat) // 必要知识：Slate的宏生成。通过这些宏自动生成委托、回调、参数的链式变编程接口
	SLATE_END_ARGS()
	void   Construct(const FArguments& InArgs);
	virtual ~SHowtoRedirectMatPanel() override;
	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;

	TSharedPtr<IDetailsView>            ViewMatPair   = nullptr; // Detail控件，给一个UObject，会将所有的UPROPERTY生成UI - UHowtoRedirectMatPairHolder 自动变成材质拾取器
	TSharedPtr<IDetailsView>            ViewParams    = nullptr; // Detail控件，给一个UObject，会将所有的UPROPERTY生成UI - UMaterialEditorInstanceConstant 自动变成参数面板
	UHowtoRedirectMatPairHolder*        MatPairHolder = nullptr; // 利用UPROPERTY自动生成UI
	UMaterialInstanceConstant*          FakeMIC       = nullptr; // 虚假的中介MIC, 用于拷贝一份SourceMIC，方便我们直接调控参数面板来编辑它并且不会污染Source
	UMaterialEditorInstanceConstant*    ParamsEdInst  = nullptr; // 负责编辑参数的工具，把用户修改过的ParamsFake拷贝到Dest上，并且它能够自动生成UI，即引擎原生MI参数面板就是依赖它
};





