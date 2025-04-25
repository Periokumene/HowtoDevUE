#pragma once

#include "CoreMinimal.h"
#include "ContentBrowserDelegates.h"


class UMaterialInstanceConstant;

namespace HowtoRedirectMatUtils
{
	namespace UI
	{
		void                                       RegisterOption();
		FContentBrowserMenuExtender_SelectedAssets CreateExtenderDelegate();
		void                                       CreateExtensionForMI(FMenuBuilder& InMenuBuilder, FAssetData Asset);
		void                                       SpawnRedirectWindow(UMaterialInstanceConstant* Mat);
	}
	namespace Exec
	{
		bool PassParams(UMaterialInstanceConstant* Source, UMaterialInstanceConstant* Dest);
	}
}
