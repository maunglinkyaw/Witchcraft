// Lin & Yin's Witchcraft 2020

#pragma once

#include "CoreMinimal.h"
#include "E_CommonEnums.h"
#include "Blueprint/UserWidget.h"
#include "CUI_EventCard.generated.h"

class UImage;
class UTextBlock;

UCLASS()
class WITCHCRAFT_API UCUI_EventCard : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UImage* EventIcon;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* EventName;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* DetailsText;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* DaysText;


	UPROPERTY(BlueprintReadOnly)
		E_EventType m_EventType;
	UPROPERTY(BlueprintReadOnly)
		FText m_EventName;
	UPROPERTY(BlueprintReadOnly)
		int m_RemainingDays;
	UPROPERTY(BlueprintReadOnly)
		bool bHasOpened;
	UPROPERTY(BlueprintReadOnly)
		bool bIsOpening;
	UPROPERTY(BlueprintReadOnly)
		bool bIsClosing;

	UFUNCTION(BlueprintCallable)
		void InitEventCard(E_EventType inEvent, FText inName, int inDays);

	UFUNCTION(BlueprintCallable)
		void AddOneDay();

	UFUNCTION(BlueprintCallable)
		void OpenEventCard();
	UFUNCTION(BlueprintCallable)
		void CloseEventCard();

	virtual void NativeTick(const FGeometry& MyGeometry, float DeltaTime) override;

protected:
	void OpeningCard(float deltaTime);
	void ClosingCard(float deltaTime);
	float m_CurrentY = 0.f;


};
