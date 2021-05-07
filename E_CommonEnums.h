// Lin & Yin's Witchcraft 2020

#pragma once

#include "CoreMinimal.h"
#include "E_CommonEnums.generated.h"


class WITCHCRAFT_API E_CommonEnums
{
public:
	//	Example usage
	//	EnumToString<E_MenuPage>("E_MenuPage", MenuPageEnum)));
	//	FString EnumString = E_CommonEnums::EnumToString(E_MenuPage, menuPage);
	template<typename TEnum>
	static FORCEINLINE FString EnumToString(const FString& Name, TEnum Value)
	{
		const UEnum* enumPtr = FindObject<UEnum>(ANY_PACKAGE, *Name, true);
		if (!enumPtr)
		{
			return FString("Invalid");
		}
		return enumPtr->GetNameByValue((int64)Value).ToString();
	}
};

#define EnumToString(EnumClassName, ValueOfEnum) EnumToString<EnumClassName>(FString(TEXT(#EnumClassName)), (ValueOfEnum))

#pragma region SYSTEMENUMS

UENUM(Blueprintable)
enum class E_MenuPage : uint8
{
	NO_MENU = 0				UMETA(DisplayName = "No Menu"),
	MAIN_MENU				UMETA(DisplayName = "Main Menu"),
	ROSTER_MENU				UMETA(DisplayName = "Roster Menu"),
	WITCH_MENU				UMETA(DisplayName = "Witch Details Menu"),
	REGION_MENU				UMETA(DisplayName = "Region Menu"),
	EVENT_MENU				UMETA(DisplayName = "Event Menu"),
	DIALOGUE_MENU			UMETA(DisplayName = "Dialogue Menu"),
	OPTIONS_MENU			UMETA(DisplayName = "Options Menu"),
	CONFIRM_MENU			UMETA(DisplayName = "Confirmation"),
};


#pragma endregion SYSTEMENUMS

#pragma region TIMEEVENT

UENUM(Blueprintable)
enum class E_TimeOfDay : uint8
{
	DAWN = 0			UMETA(DisplayName = "Dawn"),
	MORNING = 1			UMETA(DisplayName = "Morning"),
	AFTERNOON = 2		UMETA(DisplayName = "Afternoon"),
	EVENING = 3			UMETA(DisplayName = "Evening"),
	NIGHT = 4			UMETA(DisplayName = "Night"),
	WITCHINGHOUR = 5	UMETA(DisplayName = "Witching Hour"),
};

UENUM(Blueprintable)
enum class E_CalendarDay : uint8
{
	MONDAY = 0			UMETA(DisplayName = "Monday"),
	TUESDAY = 1			UMETA(DisplayName = "Tuesday"),
	WEDNESDAY = 2		UMETA(DisplayName = "Wednesday"),
	THURSDAY = 3		UMETA(DisplayName = "Thursday"),
	FRIDAY = 4			UMETA(DisplayName = "Friday"),
	SATURDAY = 5		UMETA(DisplayName = "Saturday"),
	SUNDAY = 6			UMETA(DisplayName = "Sunday"),
};

static FORCEINLINE FString DayAsString(const E_CalendarDay inDay)
{
	switch (inDay)
	{
	case E_CalendarDay::MONDAY:
		return "Monday";
		break;
	case E_CalendarDay::TUESDAY:
		return "Tuesday";
		break;
	case E_CalendarDay::WEDNESDAY:
		return "Wednesday";
		break;
	case E_CalendarDay::THURSDAY:
		return "Thursday";
		break;
	case E_CalendarDay::FRIDAY:
		return "Friday";
		break;
	case E_CalendarDay::SATURDAY:
		return "Saturday";
		break;
	case E_CalendarDay::SUNDAY:
		return "Sunday";
		break;
	};

	return "ERROR";
}


UENUM(Blueprintable)
enum class E_CalendarSeason : uint8
{
	SPRING = 0			UMETA(DisplayName = "Spring"),
	SUMMER = 1			UMETA(DisplayName = "Summer"),
	AUTUMN = 2			UMETA(DisplayName = "Autumn"),
	WINTER = 3			UMETA(DisplayName = "Winter"),
};

static FORCEINLINE FString SeasonAsString(const E_CalendarSeason inSeason)
{
	switch (inSeason)
	{
	case E_CalendarSeason::SPRING:
		return "Spring";
		break;
	case E_CalendarSeason::SUMMER:
		return "Summer";
		break;
	case E_CalendarSeason::AUTUMN:
		return "Autumn";
		break;
	case E_CalendarSeason::WINTER:
		return "Winter";
		break;
	};

	return "ERROR";
}


#pragma endregion TIMEEVENT

#define EML_COVEN		E_MapLocation::COVEN
#define EML_SHIRE		E_MapLocation::SHIRE
#define EML_CITY		E_MapLocation::CITY

UENUM(Blueprintable)
enum class E_MapRegion : uint8
{
	COVEN = 0				UMETA(DisplayName = "Coven"),
	SHIRE					UMETA(DisplayName = "Shire"),
	CITY					UMETA(DisplayName = "City"),
};

UENUM(Blueprintable)
enum class E_Witch : uint8
{
	LIRILILIA = 0			UMETA(DisplayName = "Lirililia"),
	SUMITRA					UMETA(DisplayName = "Sumitra"),
	CELESTE					UMETA(DisplayName = "Celeste"),
	SCOUT					UMETA(DisplayName = "Scout"),
};

UENUM(Blueprintable)
enum class E_EventType : uint8
{
	BREWING = 0				UMETA(DisplayName = "Brewing"),
	APPOINTMENT				UMETA(DisplayName = "Appointment"),
	QUEST					UMETA(DisplayName = "Quest"),
};


UENUM(Blueprintable)
enum class E_ActivityType : uint8
{
	NO_ACTIVITY = 0			UMETA(DisplayName = "No Activity"),
	GATHERING				UMETA(DisplayName = "Gathering"),
	CRAFTING				UMETA(DisplayName = "Crafting"),
	SELLING					UMETA(DisplayName = "Selling"),
};
