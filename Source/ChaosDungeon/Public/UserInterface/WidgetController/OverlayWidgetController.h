#pragma once

#include "CoreMinimal.h"
#include "UserInterface/WidgetController/ChaosDungeonWidgetController.h"
#include "OverlayWidgetController.generated.h"

// 声明动态组播委托
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangedSignature, float, NewMaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManaChangedSignature, float, NewMana);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxManaChangedSignature, float, NewMaxMana);

// BlueprintType : 用于将 C++ 类型（类或结构体）暴露给蓝图
// Blueprintable : 用于让 C++ 类 可以在蓝图中继承并创建蓝图子类
UCLASS(BlueprintType, Blueprintable)
class CHAOSDUNGEON_API UOverlayWidgetController : public UChaosDungeonWidgetController
{
	GENERATED_BODY()

public:
	virtual void BroadcastInitialValues() override;

public:
	// BlueprintAssignable : 允许属性在蓝图中被绑定到委托，使得该属性可以在蓝图中触发相应的函数或事件
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnHealthChangedSignature OnHealthChanged;
	
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnMaxHealthChangedSignature OnMaxHealthChanged;
	
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnManaChangedSignature OnManaChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnMaxManaChangedSignature OnMaxManaChanged;
};
