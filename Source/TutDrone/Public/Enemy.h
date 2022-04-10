// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy.generated.h"

UCLASS()
class TUTDRONE_API AEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemy();

	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnywhere)
		class UParticleSystem* ExplosionParticle;
	UPROPERTY(EditAnywhere)
		class USoundBase* ExplosionAudio;
	UPROPERTY(EditAnywhere)
		float FloatSpeed = 2000.f;

	UFUNCTION()
		void DestoryHandler(AActor* DestoryedActor);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
