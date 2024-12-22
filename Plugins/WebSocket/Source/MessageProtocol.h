#pragma once

#include "CoreMinimal.h"
#include "MessageProtocol.generated.h"

// 游戏内， 通知donation  相关数据
USTRUCT(BlueprintType)
struct FDonatePlayerInfo
{
	GENERATED_BODY()

	// 指定赠送的 网红的ID   
	UPROPERTY(BlueprintReadOnly)
	FString VTuberId; 
	
	// 指定赠送的物品 ID
	UPROPERTY(BlueprintReadOnly)
	FString ProdcutID;

	// 本次 donate 的金额   donation money this time for VTuberId
	UPROPERTY(BlueprintReadOnly)
	float DonateMoney;

	// donate 给这个 VTuber的 累计全部   donation money all for VTuberId
	UPROPERTY(BlueprintReadOnly)
	float DonateMoneyTotalVTuber;  

	// donate 给全部 VTuber的 累计全部   donation money all for all VTuberId
	UPROPERTY(BlueprintReadOnly)
	float DonateMoneyTotalAll;

	// Donate 人的 名字
	UPROPERTY(BlueprintReadOnly)
	FString DonatePlayerName;

	// Donate 人的 ID
	UPROPERTY(BlueprintReadOnly)
	FString DonatePlayerID;

	// 数据库 操作 用
	UPROPERTY(BlueprintReadOnly)
	FString BagId;
};

// 网站 请求 ，投放物品 , 目前的接口， 只支持， 一次投放一个物品， 指定一个网红
USTRUCT(BlueprintType)
struct FRequestDonateProduct
{
	GENERATED_BODY()

	// 指定赠送的 网红的ID
	UPROPERTY(BlueprintReadOnly)
	FString sVTuberId;

	// 指定赠送的物品 ID
	UPROPERTY(BlueprintReadOnly)
	FString sProdcutID;

	// 本次 donate 的金额
	UPROPERTY(BlueprintReadOnly)
	float fDonateMoney;

	// donate 给这个 VTuber的 累计全部
	UPROPERTY(BlueprintReadOnly)
	float fDonateMoneyTotalVTuber;

	// donate 给全部 VTuber的 累计全部
	UPROPERTY(BlueprintReadOnly)
	float fDonateMoneyTotalAll;

	// Donate 人的 名字
	UPROPERTY(BlueprintReadOnly)
	FString sDonatePlayerName;

	// Donate 人的 ID
	UPROPERTY(BlueprintReadOnly)
	FString sDonatePlayerID;

	// 数据库 操作 用
	UPROPERTY(BlueprintReadOnly)
	FString sBagId;

};

// 服务器返回， donate 的结果  ,
// 0 : 成功
// 1 : 解析 json 失败
// 2 : 物品配置错误
USTRUCT(BlueprintType)
struct FResponseDonateProduct
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	int32 iResult = 0;

	UPROPERTY(BlueprintReadOnly)
	FString sDonatePlayerID;

	// 数据库 操作 用
	UPROPERTY(BlueprintReadOnly)
	FString sBagId;
};
