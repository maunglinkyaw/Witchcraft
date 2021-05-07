// Lin & Yin's Witchcraft 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "C_PlayerPawn.generated.h"

UCLASS()
class WITCHCRAFT_API AC_PlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	AC_PlayerPawn();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Controls")
	class AC_PlayerController* m_PlayerController;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Controls", meta = (AllowPrivateAccess = "true"))
	class UFloatingPawnMovement* m_MovementComp;
// 	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Controls")
// 	float m_MaxX;
// 	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Controls")
// 	float m_MaxY;
// 	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Controls")
// 	float m_XOffset;



	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
	class UCameraComponent* m_Camera;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* m_CameraArm;

// 	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
// 	FRotator m_CameraStartRot;
	
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	
};
