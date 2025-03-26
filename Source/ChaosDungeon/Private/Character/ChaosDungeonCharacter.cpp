#include "Character/ChaosDungeonCharacter.h"
#include "PlayerState/ChaosDungeonPlayerState.h"
#include "PlayerController/ChaosDungeonPlayerController.h"
#include "UserInterface/HUD/ChaosDungeonHUD.h"
#include "AbilitySystem/DoCAbilitySystemComponent.h"

// Engine
#include "AbilitySystemComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AChaosDungeonCharacter::AChaosDungeonCharacter()
{
	bUseControllerRotationYaw = false;

	// 角色的朝向自动匹配移动方向
	GetCharacterMovement()->bOrientRotationToMovement = true;
	// 旋转速率
	GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f);
	GetCharacterMovement()->JumpZVelocity = 300.f;
	GetCharacterMovement()->AirControl = 0.2f;
	//GetCharacterMovement()->bUseControllerDesiredRotation = false;
	// 限制角色或物体的移动在特定的平面上
	//GetCharacterMovement()->bConstrainToPlane = true;
	// 在游戏开始时自动将对象对齐到约束平面
	//GetCharacterMovement()->bSnapToPlaneAtStart = true;
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->TargetArmLength = 600.f;
	CameraBoom->bUsePawnControlRotation = true;
	// 平滑相机
	//CameraBoom->bEnableCameraLag = true;
	//CameraBoom->CameraLagSpeed = 3.f;
	// 防止摄像机跟随角色上下看
	//CameraBoom->bInheritPitch = false;
	// 不跟随角色转向
	//CameraBoom->bInheritYaw = false;
	// 防止摄像机在坡道上倾斜
	//CameraBoom->bInheritRoll = false;
	// 弹簧臂进行碰撞检测，防止摄像机穿墙自动缩短
	CameraBoom->bDoCollisionTest = true;
	CameraBoom->SetupAttachment(GetRootComponent());

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->bUsePawnControlRotation = false;
	//FollowCamera->FieldOfView = 90.f;
	FollowCamera->SetupAttachment(CameraBoom);
}

void AChaosDungeonCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Init ability actor info for the server
	InitAbilityActorInfo();

	AddCharacterAbilities();
}

void AChaosDungeonCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// Init ability actor info for the client
	InitAbilityActorInfo();
}

int32 AChaosDungeonCharacter::GetPlayerLevel() const
{
	AChaosDungeonPlayerState* ChaosDungeonPlayerState = Cast<AChaosDungeonPlayerState>(GetPlayerState());

	check(ChaosDungeonPlayerState);

	return ChaosDungeonPlayerState->GetPlayerLevel();
}

void AChaosDungeonCharacter::InitAbilityActorInfo()
{
	// 获取玩家状态
	AChaosDungeonPlayerState* ChaosDungeonPlayerState = Cast<AChaosDungeonPlayerState>(GetPlayerState());
	check(ChaosDungeonPlayerState);

	// 玩家状态类继承 IAbilitySystemInterface,实现 GetAbilitySystemComponent() 纯虚函数
	// 初始化 InitAbilityActorInfo：OwnerActor - 玩家状态，AvatarActor - 角色
	ChaosDungeonPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(ChaosDungeonPlayerState, this);

	Cast<UDoCAbilitySystemComponent>(ChaosDungeonPlayerState->GetAbilitySystemComponent())->AbilityActorInfoSet();

	AbilitySystemComponent = ChaosDungeonPlayerState->GetAbilitySystemComponent();
	AttributeSet = ChaosDungeonPlayerState->GetAttributeSet();
	
	if (AChaosDungeonPlayerController* ChaosDungeonPlayerController = Cast<AChaosDungeonPlayerController>(GetController()))
	{
		if (AChaosDungeonHUD* ChaosDungeonHUD = Cast<AChaosDungeonHUD>(ChaosDungeonPlayerController->GetHUD()))
		{
			// 初始化 HUD
			ChaosDungeonHUD->InitOverlay(ChaosDungeonPlayerController, ChaosDungeonPlayerState, AbilitySystemComponent, AttributeSet);
		}
	}

	// 初始化主属性
	InitializeDefaultAttributes();
}