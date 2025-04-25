#pragma once

#include "CoreMinimal.h"


namespace HowtoFixContent
{
	
namespace UI
{
	void                  Folder_RegisterMenuExtender();
	TSharedRef<FExtender> Folder_MenuExtenderGet(const TArray<FString>& Folders);
	void                  Folder_SpawnFixPanel(TArray<FString> Folders);
	
}


namespace Core
{
	void CollectAssetsByFolder(FString Folder, TSet<FAssetData>& OutAssets);
}
	
}