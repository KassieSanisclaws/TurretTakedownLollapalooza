// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	Health = MaxHealth; // Initialize health to max health

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken); // Bind the damage event

}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, class AController* Instigator, AActor* DamageCauser)
{
	if (Damage <= 0.0f || Health <= 0.0f) return; // Ignore non-positive damage or if health is already zero

	Health -= Damage; // Reduce health by the damage amount

	UE_LOG(LogTemp, Warning, TEXT("Health: %f"), Health); // Log the current health

	// Optionally, you can trigger events or animations here based on the health change
	if (Health <= 0.0f)
	{
		// Handle death logic here, e.g., destroy the actor or trigger a death animation
		GetOwner()->Destroy(); // Example: destroy the owner actor
	}
	else
	{
		// Optionally, handle logic for when health is still above zero, like playing a hurt animation or sound
	}
}
