#pragma once

#include "CoreMinimal.h"
#include "MessageProtocol.generated.h"

// ��Ϸ�ڣ� ֪ͨdonation  �������
USTRUCT(BlueprintType)
struct FDonatePlayerInfo
{
	GENERATED_BODY()

	// ָ�����͵� �����ID   
	UPROPERTY(BlueprintReadOnly)
	FString VTuberId; 
	
	// ָ�����͵���Ʒ ID
	UPROPERTY(BlueprintReadOnly)
	FString ProdcutID;

	// ���� donate �Ľ��   donation money this time for VTuberId
	UPROPERTY(BlueprintReadOnly)
	float DonateMoney;

	// donate ����� VTuber�� �ۼ�ȫ��   donation money all for VTuberId
	UPROPERTY(BlueprintReadOnly)
	float DonateMoneyTotalVTuber;  

	// donate ��ȫ�� VTuber�� �ۼ�ȫ��   donation money all for all VTuberId
	UPROPERTY(BlueprintReadOnly)
	float DonateMoneyTotalAll;

	// Donate �˵� ����
	UPROPERTY(BlueprintReadOnly)
	FString DonatePlayerName;

	// Donate �˵� ID
	UPROPERTY(BlueprintReadOnly)
	FString DonatePlayerID;

	// ���ݿ� ���� ��
	UPROPERTY(BlueprintReadOnly)
	FString BagId;
};

// ��վ ���� ��Ͷ����Ʒ , Ŀǰ�Ľӿڣ� ֻ֧�֣� һ��Ͷ��һ����Ʒ�� ָ��һ������
USTRUCT(BlueprintType)
struct FRequestDonateProduct
{
	GENERATED_BODY()

	// ָ�����͵� �����ID
	UPROPERTY(BlueprintReadOnly)
	FString sVTuberId;

	// ָ�����͵���Ʒ ID
	UPROPERTY(BlueprintReadOnly)
	FString sProdcutID;

	// ���� donate �Ľ��
	UPROPERTY(BlueprintReadOnly)
	float fDonateMoney;

	// donate ����� VTuber�� �ۼ�ȫ��
	UPROPERTY(BlueprintReadOnly)
	float fDonateMoneyTotalVTuber;

	// donate ��ȫ�� VTuber�� �ۼ�ȫ��
	UPROPERTY(BlueprintReadOnly)
	float fDonateMoneyTotalAll;

	// Donate �˵� ����
	UPROPERTY(BlueprintReadOnly)
	FString sDonatePlayerName;

	// Donate �˵� ID
	UPROPERTY(BlueprintReadOnly)
	FString sDonatePlayerID;

	// ���ݿ� ���� ��
	UPROPERTY(BlueprintReadOnly)
	FString sBagId;

};

// ���������أ� donate �Ľ��  ,
// 0 : �ɹ�
// 1 : ���� json ʧ��
// 2 : ��Ʒ���ô���
USTRUCT(BlueprintType)
struct FResponseDonateProduct
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	int32 iResult = 0;

	UPROPERTY(BlueprintReadOnly)
	FString sDonatePlayerID;

	// ���ݿ� ���� ��
	UPROPERTY(BlueprintReadOnly)
	FString sBagId;
};
