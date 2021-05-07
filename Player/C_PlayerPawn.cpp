// Lin & Yin's Witchcraft 2020

#include "C_PlayerPawn.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SceneComponent.h"

 
AC_PlayerPawn::AC_PlayerPawn()
{
	PrimaryActorTick.bCanEverTick = true;
	
	SetActorEnableCollision(false);

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));

	m_MovementComp = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Floating Movement"));

	// Create a camera boom attached to the root (capsule)
	m_CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	m_CameraArm->SetupAttachment(RootComponent);
	m_CameraArm->SetAbsolute(false, true, false); // Rotation of the character should not affect rotation of boom
	m_CameraArm->bDoCollisionTest = false;
	m_CameraArm->TargetArmLength = 500.f;
	m_CameraArm->SocketOffset = FVector(0.f, 0.f, 0.f);
	m_CameraArm->SetRelativeRotation(FRotator(-50.f, 0.f, 0.f));

	m_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("World Camera"));
	//m_Camera->SetupAttachment(GetRootComponent());
	m_Camera->SetupAttachment(m_CameraArm, USpringArmComponent::SocketName);
	m_Camera->SetProjectionMode(ECameraProjectionMode::Perspective);
	m_Camera->SetFieldOfView(90.f);
	//m_Camera->SetRelativeRotation(m_CameraStartRot);

}

void AC_PlayerPawn::BeginPlay()
{
	Super::BeginPlay();

}

void AC_PlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}