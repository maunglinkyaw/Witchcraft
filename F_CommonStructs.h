// Lin & Yin's Witchcraft 2020

#pragma once

#include "CoreMinimal.h"
#include "E_CommonEnums.h"
#include "F_CommonStructs.generated.h"

USTRUCT(Blueprintable)
struct F_Date
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
		int date = 1;
	UPROPERTY(VisibleAnywhere)
		E_TimeOfDay timeOfDay = E_TimeOfDay::MORNING;
	UPROPERTY(VisibleAnywhere)
		E_CalendarDay day = E_CalendarDay::MONDAY;
	UPROPERTY(VisibleAnywhere)
		int month = 1;
	UPROPERTY(VisibleAnywhere)
		E_CalendarSeason season = E_CalendarSeason::SPRING;
	UPROPERTY(VisibleAnywhere)
		int year = 1;
	UPROPERTY(VisibleAnywhere)
		int ymmdd = 10101;

	bool IsWeekend()
	{
		return ((int)day > 4);
	}

	//Get Date as string
	FString DateToString()
	{
		FString dateString = FString::FromInt(date);
		dateString.Append(", Month");
		dateString = FString::FromInt(month);
		dateString.Append(", Year ");
		dateString = FString::FromInt(year);
		return dateString;
	}

	//Constructors
	F_Date(int newDate = 0, int newMonth = 0, int newYear = 0, int newTimeOfDay = 0)
	{
		date = newDate;
		month = newMonth;
		year = newYear;
		timeOfDay = E_TimeOfDay(newTimeOfDay);

		if (newDate != 0)
		{
			int totalDays = date - 1;
			totalDays += (month - 1) * 30;
			totalDays += (year - 1) * 360;

			if (totalDays < 0)
			{
				totalDays = 0;
			}
			day = E_CalendarDay(totalDays % 7);

			season = E_CalendarSeason((int)(month / 3));

			ymmdd = year * 10000 + month * 100 + date;
		}
	}

	bool operator>(const F_Date& Other) const
	{
		return (ymmdd > Other.ymmdd);
	}

	bool operator>=(const F_Date& Other) const
	{
		return (ymmdd >= Other.ymmdd);
	}

	bool operator<(const F_Date& Other) const
	{
		return (ymmdd < Other.ymmdd);
	}

	bool operator<=(const F_Date& Other) const
	{
		return (ymmdd <= Other.ymmdd);
	}
};

USTRUCT(Blueprintable)
struct F_Event
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName eventName;

	F_Event()
	{

	}
};
