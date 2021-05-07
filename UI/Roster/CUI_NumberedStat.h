// Lin & Yin's Witchcraft 2020

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CUI_NumberedStat.generated.h"


class UTextBlock;

UCLASS()
class WITCHCRAFT_API UCUI_NumberedStat : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* StatName;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* StatNum;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FText StatDisplayName = FText::FromString("Stat Name");

	void SetStat(int32 inStat);
	void SetProgress(float newProgress);
};
