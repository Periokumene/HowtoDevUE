#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "HowtoFixContentMisc.generated.h"



UENUM()
enum class EHowtoFixContent_MatCat
{
	Default UMETA(DisplayName="默认"),
	Weather UMETA(DisplayName="天气"),
	Weapon  UMETA(DisplayName="武器"),
};

UENUM()
enum class EHowtoFixContent_TexCat
{
	Default,
	Weather,
	Misc,
};
