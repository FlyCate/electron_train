<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<title>ViKey--API����</title>
<link href="ViKeyTest.css" rel="stylesheet" type="text/css">
<embed id="ViKeyInterface"  type="application/npViKeyInterface-plugin" style="height: 0;width: 0; "> </embed>

<?php
	$ViKeyInterface = new COM("ViKeyActiveX.ViKeyInterface.1");
	$ViKeyInterfaceVersion = $ViKeyInterface->IGetVersion();
	
	$ViKeyCount = $ViKeyInterface->IVikeyFind();
	
	if($ViKeyInterface->IViKeyGetError() ==0)	
	{
		echo "���ҵ����ܹ������� ".$ViKeyCount."<br />";
		$ViKeyIndex = 0;
		$ViKeyInterface->IVikeyUserLogin($ViKeyIndex, "11111111");
		if($ViKeyInterface->IViKeyGetError() ==0)	
		{
			echo "�û���½���ܹ��ɹ�! <br />";
		}
		else
		{
			echo "�û���½���ܹ�ʧ��<br /> ";
		}

		$ViKeyInterface->IVikeyAdminLogin($ViKeyIndex, "00000000");
		if($ViKeyInterface->IViKeyGetError() ==0)	
		{
			echo "����Ա��½���ܹ��ɹ�! <br />";
		}
		else
		{
			echo "����Ա��½���ܹ�ʧ�� <br /> ";
		}
		
		$ViKeySID = $ViKeyInterface->IVikeyGetSoftIDString($ViKeyIndex);
		if($ViKeyInterface->IViKeyGetError() ==0)	
		{
			echo "��ȡ���ID�ɹ�- ".$ViKeySID ."<br />";
		}
		else
		{
			echo "��ȡ���ID�ɹ�ʧ��<br /> ";
		}	

		$Addr= 0;
		$Length = 8;
		$Data="12345678";
		$ViKeyInterface->IVikeyWriteData($ViKeyIndex, $Addr, $Length, $Data);
		if($ViKeyInterface->IViKeyGetError() ==0)	
		{
			echo "д�����ݳɹ�: ".$Data."<br />";
		}
		else
		{
			echo "д������ʧ�� <br />";
		}

		$ReadBuffer =$ViKeyInterface->IVikeyReadData($ViKeyIndex, $Addr, $Length);
		if($ViKeyInterface->IViKeyGetError() ==0)	
		{
			echo "�������ݳɹ�: ".$ReadBuffer."<br />";
		}
		else
		{
			echo "��������ʧ�� <br />";
		}

		$ViKeyInterface->IVikeyLogoff($ViKeyIndex);
		if($ViKeyInterface->IViKeyGetError() ==0)	
		{
			echo "ע�����ܹ��ɹ�";
		}
		else
		{
			echo "ע�����ܹ�ʧ�� <br />";
		}
		
	}
	else
	{
		echo "û�в��Ҽ��ܹ�";
	}
	
?>
</head>
<body>
<div align="center">
              <span class="blue01">ViKey API����_�ؼ��汾��<?php echo $ViKeyInterfaceVersion; ?></span>

</div>

</body>
</html>
