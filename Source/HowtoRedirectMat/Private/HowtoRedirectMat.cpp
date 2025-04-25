#include "HowtoRedirectMat.h"

#include "HowtoRedirectMatUtils.h"

#define LOCTEXT_NAMESPACE "FHowtoRedirectMatModule"

void FHowtoRedirectMatModule::
StartupModule()
{
    HowtoRedirectMatUtils::UI::RegisterOption();
}

void FHowtoRedirectMatModule::
ShutdownModule()
{
    
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FHowtoRedirectMatModule, HowtoRedirectMat)