// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"
#include "../Public/Enemy.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpawnArea = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnArea"));
	RootComponent = SpawnArea;
	SpawnArea->SetBoxExtent(FVector(10000.f, 10000.f, 40.f));
	InitialLifeSpan = 10.f;
}

void AEnemySpawner::SpawnEnemy()
{
	FVector Origin;
	FVector Extends;
	GetActorBounds(false, Origin, Extends);
	FVector spawnPoint = UKismetMathLibrary::RandomPointInBoundingBox(Origin, Extends);
	GetWorld()->SpawnActor<AEnemy>(Enemy, spawnPoint, FRotator::ZeroRotator);
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorld()->GetTimerManager().SetTimer(SpawnHandler, this, &AEnemySpawner::SpawnEnemy, 2.f, true);
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

