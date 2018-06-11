<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<title>ViKey--API测试</title>
<link href="ViKeyTest.css" rel="stylesheet" type="text/css">
<embed id="ViKeyInterface"  type="application/npViKeyInterface-plugin" style="height: 0;width: 0; "> </embed>

<?php
	$ViKeyInterface = new COM("ViKeyActiveX.ViKeyInterface.1");
	$ViKeyInterfaceVersion = $ViKeyInterface->IGetVersion();
	
	$ViKeyCount = $ViKeyInterface->IVikeyFind();
	
	if($ViKeyInterface->IViKeyGetError() ==0)	
	{
		echo "查找到加密狗个数： ".$ViKeyCount."<br />";
		$ViKeyIndex = 0;
		$ViKeyInterface->IVikeyUserLogin($ViKeyIndex, "11111111");
		if($ViKeyInterface->IViKeyGetError() ==0)	
		{
			echo "用户登陆加密狗成功! <br />";
		}
		else
		{
			echo "用户登陆加密狗失败<br /> ";
		}

		$ViKeyInterface->IVikeyAdminLogin($ViKeyIndex, "00000000");
		if($ViKeyInterface->IViKeyGetError() ==0)	
		{
			echo "管理员登陆加密狗成功! <br />";
		}
		else
		{
			echo "管理员登陆加密狗失败 <br /> ";
		}
		
		$ViKeySID = $ViKeyInterface->IVikeyGetSoftIDString($ViKeyIndex);
		if($ViKeyInterface->IViKeyGetError() ==0)	
		{
			echo "获取软件ID成功- ".$ViKeySID ."<br />";
		}
		else
		{
			echo "获取软件ID成功失败<br /> ";
		}	

		$Addr= 0;
		$Length = 8;
		$Data="12345678";
		$ViKeyInterface->IVikeyWriteData($ViKeyIndex, $Addr, $Length, $Data);
		if($ViKeyInterface->IViKeyGetError() ==0)	
		{
			echo "写入数据成功: ".$Data."<br />";
		}
		else
		{
			echo "写入数据失败 <br />";
		}

		$ReadBuffer =$ViKeyInterface->IVikeyReadData($ViKeyIndex, $Addr, $Length);
		if($ViKeyInterface->IViKeyGetError() ==0)	
		{
			echo "读出数据成功: ".$ReadBuffer."<br />";
		}
		else
		{
			echo "读出数据失败 <br />";
		}

		$ViKeyInterface->IVikeyLogoff($ViKeyIndex);
		if($ViKeyInterface->IViKeyGetError() ==0)	
		{
			echo "注销加密狗成功";
		}
		else
		{
			echo "注销加密狗失败 <br />";
		}
		
	}
	else
	{
		echo "没有查找加密狗";
	}
	
?>
</head>
<body>
<div align="center">
              <span class="blue01">ViKey API测试_控件版本：<?php echo $ViKeyInterfaceVersion; ?></span>

</div>

</body>
</html>
