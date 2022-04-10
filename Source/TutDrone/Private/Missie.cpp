// Fill out your copyright notice in the Description page of Project Settings.


#include "Missie.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Enemy.h"
#include "../TutDroneGameModeBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMissie::AMissie()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetGenerateOverlapEvents(true);
	Mesh->OnComponentBeginOverlap.AddDynamic(this, &AMissie::OverlapHandler);
	RootComponent = Mesh;
	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComp"));
	MovementComp->InitialSpeed = 2000.f;
	InitialLifeSpan = 5.0f;
}

void AMissie::OverlapHandler(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA<AEnemy>())
	{
		OtherActor->Destroy();
		ATutDroneGameModeBase* gameMode = Cast<ATutDroneGameModeBase>(GetWorld()->GetAuthGameMode());
		if (gameMode != nullptr)
		{
			gameMode->score++;
		}
		this->Destroy();
	}
}

// Called when the game starts or when spawned
void AMissie::BeginPlay()
{
	Super::BeginPlay();
	UGameplayStatics::PlaySound2D(this, FireAudio);
}

// Called every frame
void AMissie::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

