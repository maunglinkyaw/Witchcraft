// Lin & Yin's Witchcraft 2020

#pragma once

#include "CoreMinimal.h"
//#include "UI/CUI_Button.h"
#include "Blueprint/UserWidget.h"
#include "CUI_WorldLabel.generated.h"

class UImage;
class UTextBlock;
class UInvalidationBox;

UCLASS()
class WITCHCRAFT_API UCUI_WorldLabel : public UUserWidget
{
	GENERATED_BODY()

public:
// 	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
// 	UInvalidationBox* InvalidBox;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UImage* LabelIcon;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* NameText;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UImage* StatusIcon;

	void UpdateLabelName(const FText& inName);
};
