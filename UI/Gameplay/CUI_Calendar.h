// Lin & Yin's Witchcraft 2020

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "F_CommonStructs.h"
#include "CUI_Calendar.generated.h"

class AC_TimeManager;
class UImage;
class UTextBlock;
class UButton;
class UWidgetSwitcher;

UCLASS()
class WITCHCRAFT_API UCUI_Calendar : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UImage* WheelImage;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* DateText;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* DayText;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* MonthText;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* YearText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UScrollBox* EventScrollBox;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UWidgetSwitcher* ButtonSwitcher;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UHorizontalBox* ButtonsBox;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UHorizontalBox* StopBox;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UHorizontalBox* BackToMapBox;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UButton* GoButton;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UTextBlock* GoButtonText;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UButton* AutoRunButton;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UTextBlock* AutoRunButtonText;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UButton* StopButton;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UTextBlock* StopButtonText;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UButton* BackToMapButton;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UTextBlock* BackToMapButtonText;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	AC_TimeManager* m_TimeManager;

	void InitCalendarWidget(AC_TimeManager* timeManager);
	
	UFUNCTION(BlueprintCallable)
	void StartTheClock(bool isAutoRun);
	UFUNCTION(BlueprintCallable)
	void StopTheClock();
	UFUNCTION(BlueprintCallable)
	void ToggleButtonSwitcher(int newIndex);


	UFUNCTION(BlueprintCallable)
	void SetDateTo(F_Date newDate);
	void GoNextDay(F_Date newDate);

	void UpdateTimeOfDay(E_TimeOfDay newTime);

};
