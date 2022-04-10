// Fill out your copyright notice in the Description page of Project Settings.


#include "Drone.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "PhysicsEngine/PhysicsThrusterComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ADrone::ADrone()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	OutCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("OutCollision"));
	RootComponent = OutCollision;
	OutCollision->SetBoxExtent(FVector(90.f, 90.f, 40.f));
	OutCollision->SetSimulatePhysics(true); // 开启物理模拟
	OutCollision->BodyInstance.bLockXRotation = true; // 锁定X轴旋转
	OutCollision->BodyInstance.bLockYRotation = true; // 锁定Y轴旋转
	OutCollision->SetCollisionProfileName(TEXT("Pawn"));


	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(OutCollision);
	Paddle1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Paddle1"));
	Paddle2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Paddle2"));
	Paddle3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Paddle3"));
	Paddle4 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Paddle4"));

	Paddle1->SetupAttachment(Mesh, TEXT("Paddle1"));
	Paddle2->SetupAttachment(Mesh, TEXT("Paddle2"));
	Paddle3->SetupAttachment(Mesh, TEXT("Paddle3"));
	Paddle4->SetupAttachment(Mesh, TEXT("Paddle4"));
	Paddles.Add(Paddle1);
	Paddles.Add(Paddle2);
	Paddles.Add(Paddle3);
	Paddles.Add(Paddle4);

	UpThruster = CreateDefaultSubobject<UPhysicsThrusterComponent>(TEXT("UpThruster"));
	UpThruster->SetupAttachment(RootComponent);
	UpThruster->ThrustStrength = 980.0f;
	UpThruster->SetAutoActivate(true);
	UpThruster->SetWorldRotation(UKismetMathLibrary::MakeRotFromX(-this->GetActorUpVector()));

	ForwardThruster = CreateDefaultSubobject<UPhysicsThrusterComponent>(TEXT("ForwardThruster"));
	ForwardThruster->SetupAttachment(RootComponent);
	ForwardThruster->ThrustStrength = 0.f;
	ForwardThruster->SetAutoActivate(true);
	ForwardThruster->SetWorldRotation(UKismetMathLibrary::MakeRotFromX(-this->GetActorForwardVector()));

}

// Called when the game starts or when spawned
void ADrone::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADrone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetInputAxisValue(TEXT("Lift")) == 0)
	{
		UpThruster->ThrustStrength = 980.f;
	}
	if (GetInputAxisValue(TEXT("Forward")) == 0)
	{
		ForwardThruster->ThrustStrength = 0.f;
		if (Mesh->GetRelativeRotation().Pitch != 0)
		{
			float currentPitch = Mesh->GetRelativeRotation().Pitch;
			Mesh->AddRelativeRotation(FRotator(-currentPitch*DeltaTime, 0.f, 0.f));
			if (FMath::Abs(Mesh->GetRelativeRotation().Pitch) <= KINDA_SMALL_NUMBER)
			{
				Mesh->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));
			}
		}
	}
	if (GetInputAxisValue(TEXT("Turn")) == 0)
	{
	}
	RotatePaddle(DeltaTime);
}

// Called to bind functionality to input
void ADrone::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Lift"), this, &ADrone::Lift);
	PlayerInputComponent->BindAxis(TEXT("Forward"), this, &ADrone::Forward);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ADrone::Turn);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ADrone::Fire);
}

void ADrone::Lift(float Input)
{
	float temp = UpThruster->ThrustStrength + Input*LiftAcc*GetWorld()->DeltaTimeSeconds;
	UpThruster->ThrustStrength = FMath::Clamp(temp, -LiftMaxThrust, LiftMaxThrust);
}

void ADrone::Forward(float Input)
{
	float temp = ForwardThruster->ThrustStrength + Input * ForwardAcc * GetWorld()->DeltaTimeSeconds;
	ForwardThruster->ThrustStrength = FMath::Clamp(temp, -ForwardMaxThrust, ForwardMaxThrust);

	float pitch = Mesh->GetRelativeRotation().Pitch;
	if (FMath::Abs(pitch) <= 30.f)
	{
		Mesh->AddRelativeRotation(FRotator(-Input * 50.f * GetWorld()->DeltaTimeSeconds, 0.f, 0.f));
	}
}

void ADrone::Turn(float Input)
{
	OutCollision->AddTorqueInRadians(-this->GetActorUpVector() * Input * TurnStrangth * GetWorld()->DeltaTimeSeconds);
}

void ADrone::Fire()
{
	GetWorld()->SpawnActor<AMissie>(Bullet, Mesh->GetSocketTransform(TEXT("Firing")));
}

void ADrone::RotatePaddle(float deltaTime)
{
	for (auto paddle : Paddles)
	{
		paddle->AddRelativeRotation(FRotator(0.f, PaddleRotateSpeed * deltaTime, 0.f));
	}
}

