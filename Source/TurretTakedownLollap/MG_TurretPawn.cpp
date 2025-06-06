// Fill out your copyright notice in the Description page of Project Settings.


#include "MG_TurretPawn.h"
#include "Components/StaticMeshComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "Components/SceneComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values
AMG_TurretPawn::AMG_TurretPawn()
{
    // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // Create and set Root Component
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	// Create & attach the static Mesh to Root
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMesh"));
	TurretMesh->SetupAttachment(Root);

	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
	PawnSensingComp->SightRadius = 2000.f; // Set the sensing radius
	PawnSensingComp->SetPeripheralVisionAngle(95.f); // Set the peripheral vision angle
	PawnSensingComp->bSeePawns = true; // Enable seeing pawns
	PawnSensingComp->bHearNoises = false; // Disable hearing noises
	PawnSensingComp->bOnlySensePlayers = false; // Allow sensing all pawns, not just players
	PawnSensingComp->SetAutoActivate(true); // Automatically activate the component
	PawnSensingComp->PrimaryComponentTick.bCanEverTick = true; // Turning on ticking for Pawn Sensing Component

	

	// Create and attach Pawn Sensing component to Root
	
	/*PawnSensingComp->SetupAttachment(Root);*/ // No need to attach to Root, it will be automatically attached to the RootComponent
}

// Called when the game starts or when spawned
void AMG_TurretPawn::BeginPlay()
{
	Super::BeginPlay();
  
	// DEBUG: Print to screen
	/*DrawDebugSphere(GetWorld(), GetActorLocation(), PawnSensingComp->SightRadius, 32, FColor::Red, true, 10.f);*/

	/*PawnSensingComp->Activate();*/ // Ensure the Pawn Sensing Component is active
	// Bind the OnSeePawn event to our custom function
	if (PawnSensingComp)
	{
		/*DrawDebugSphere(GetWorld(), GetActorLocation(), PawnSensingComp->SightRadius, 32, FColor::Red, true, 10.f);*/
		UE_LOG(LogTemp, Warning, TEXT("PawnSensingComp found, binding delegate."));
		PawnSensingComp->OnSeePawn.AddDynamic(this, &AMG_TurretPawn::OnPawnSeen);
	}
	else 
	{
		UE_LOG(LogTemp, Error, TEXT("PawnSensingComp is null! in BeginPlay"));
	}
}

// Called every frame
void AMG_TurretPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMG_TurretPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMG_TurretPawn::OnPawnSeen(APawn* SeenPawn)
{
	if (!SeenPawn) return;

	// DEBUG: Print to screen
	UKismetSystemLibrary::PrintString(this, TEXT("Pawn Seen!"), true, true, FLinearColor::Red, 2.0f);
	UE_LOG(LogTemp, Warning, TEXT("Pawn Seen: %s"), *SeenPawn->GetClass()->GetName());
	/*UE_LOG(LogTemp, Warning, TEXT("Seen Pawn: %s"), *SeenPawn->GetName());*/

	// Optional: Make sure it's the player or character
	/*ACharacter* PlayerCharacter = Cast<ACharacter>(SeenPawn);
	if (!PlayerCharacter) return;*/

	FVector TargetLocation = SeenPawn->GetActorLocation();
	FVector OwnLocation = GetActorLocation();

	FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(OwnLocation, TargetLocation);

	// Apply only Yaw to rotate horizontally
	SetActorRotation(FRotator(0.f, LookAtRotation.Yaw, 0.f));
}

