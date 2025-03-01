#include "Character/ChaosDungeonCharacter.h"

// Engine
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AChaosDungeonCharacter::AChaosDungeonCharacter()
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// 角色的朝向自动匹配移动方向
	GetCharacterMovement()->bOrientRotationToMovement = true;
	// 旋转速率
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	// 限制角色或物体的移动在特定的平面上
	GetCharacterMovement()->bConstrainToPlane = true;
	// 在游戏开始时自动将对象对齐到约束平面
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->bUsePawnControlRotation = false;
	// 防止摄像机跟随角色上下看
	CameraBoom->bInheritPitch = false;
	// 不跟随角色转向
	CameraBoom->bInheritYaw = false;
	// 防止摄像机在坡道上倾斜
	CameraBoom->bInheritRoll = false;
	// 弹簧臂进行碰撞检测，防止摄像机穿墙自动缩短
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->SetupAttachment(GetRootComponent());

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->bUsePawnControlRotation = false;
	FollowCamera->SetupAttachment(CameraBoom);
}
