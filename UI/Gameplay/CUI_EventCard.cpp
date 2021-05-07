// Lin & Yin's Witchcraft 2020


#include "CUI_EventCard.h"
#include "TextBlock.h"
#include "Image.h"


void UCUI_EventCard::InitEventCard(E_EventType inEvent, FText inName, int inDays)
{
	m_EventName = inName;
	m_EventType = inEvent;
	m_RemainingDays = inDays;

	switch (m_EventType)
	{
	case E_EventType::BREWING:
	{
		EventIcon->SetColorAndOpacity(FLinearColor::Green);
		DetailsText->SetText(FText::FromString("Brewing"));
	}
	break;

	case E_EventType::QUEST:
	{
		EventIcon->SetColorAndOpacity(FLinearColor::Blue);
		DetailsText->SetText(FText::FromString("Quest"));
	}
	break;

	};

	EventName->SetText(m_EventName);
	DaysText->SetText(FText::AsNumber(m_RemainingDays));
}

void UCUI_EventCard::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
	if (bIsClosing)
	{
		ClosingCard(DeltaTime);
	}
	else if (bIsOpening)
	{
		OpeningCard(DeltaTime);
	}

	Super::NativeTick(MyGeometry, DeltaTime);
}

void UCUI_EventCard::AddOneDay()
{
	m_RemainingDays--;

	if (m_RemainingDays < 0)
	{
		DaysText->SetText(FText::AsNumber(0));
	}
	else
	{
		DaysText->SetText(FText::AsNumber(m_RemainingDays));
	}
}

void UCUI_EventCard::OpenEventCard()
{
	bIsOpening = true;
}

void UCUI_EventCard::CloseEventCard()
{
	bIsClosing = true;
}

void UCUI_EventCard::OpeningCard(float deltaTime)
{
	float desiredY = FMath::FInterpConstantTo(m_CurrentY, 1.1f, deltaTime, 5.f);

	if (FMath::IsNearlyEqual(desiredY, 1.1f, 0.01f))
	{
		desiredY = 1.f;
		bIsOpening = false;
		bHasOpened = true;
	}

	m_CurrentY = desiredY;
	SetRenderScale(FVector2D(1.f, desiredY));
}

void UCUI_EventCard::ClosingCard(float deltaTime)
{
	float desiredY = FMath::FInterpConstantTo(m_CurrentY, 0.f, deltaTime, 5.f);

	m_CurrentY = desiredY;
	SetRenderScale(FVector2D(1.f, desiredY));

	if (FMath::IsNearlyEqual(desiredY, 0.f, 0.01f))
	{
		bIsClosing = false;
		RemoveFromParent();
	}
}
