// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Missie.h"
#include "Drone.generated.h"

UCLASS()
class TUTDRONE_API ADrone : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ADrone();

	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* Mesh;
	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* Paddle1;
	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* Paddle2;
	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* Paddle3;
	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* Paddle4;
	UPROPERTY(EditAnywhere)
		TSubclassOf<AMissie> Bullet;


	UPROPERTY(VisibleAnywhere)
		class UBoxComponent* OutCollision;

	UPROPERTY(VisibleAnywhere)
		class UPhysicsThrusterComponent* UpThruster;
	UPROPERTY(VisibleAnywhere)
		class UPhysicsThrusterComponent* ForwardThruster;

	UPROPERTY(EditAnywhere)
		float LiftAcc = 1000.f;
	UPROPERTY(EditAnywhere)
		float ForwardAcc = 500.f;
	UPROPERTY(EditAnywhere)
		float TurnStrangth = 500000.f;

	UPROPERTY(EditAnywhere)
		float LiftMaxThrust = 2000.f;
	UPROPERTY(EditAnywhere)
		float ForwardMaxThrust = 1000.f;
	UPROPERTY(EditAnywhere)
		float PaddleRotateSpeed = 2000.f;

private:
	UFUNCTION()
		void Lift(float Input);
	UFUNCTION()
		void Forward(float Input);
	UFUNCTION()
		void Turn(float Input);
	UFUNCTION()
		void Fire();

	TArray<UStaticMeshComponent*> Paddles;
	void RotatePaddle(float deltaTime);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
