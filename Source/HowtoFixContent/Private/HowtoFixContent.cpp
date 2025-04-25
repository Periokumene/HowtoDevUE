#include "HowtoFixContent.h"

#include "HowtoFixContentUtils.h"

#define LOCTEXT_NAMESPACE "FHowtoFixContentModule"

void FHowtoFixContentModule::
StartupModule()
{
    HowtoFixContent::UI::Folder_RegisterMenuExtender();
}

void FHowtoFixContentModule::
ShutdownModule()
{
    
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FHowtoFixContentModule, HowtoFixContent)