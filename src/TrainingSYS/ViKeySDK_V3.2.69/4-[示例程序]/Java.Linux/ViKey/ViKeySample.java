package ViKey;

class ViKeyJavaObj
{
	static
	{
		System.loadLibrary("ViKeyJavaObj");
	}

	private native int ViKeyFind(int[] lpdwCount);
    private native int ViKeyGetType(short Index, byte[] pType);
	private native int ViKeyGetHID(short Index, int[] pdwHID);
	
    private native int VikeyGetLevel(short Index, byte[] pLevel);
    private native int ViKeyUserLogin(short Index, byte[] pPassWord);
    private native int ViKeyAdminLogin(short Index,  byte[] pPassWord);
    private native int ViKeyLogoff(short Index);

    private native int VikeySetUserPassWordAttempt(short Index, byte cAttempt);
    private native int VikeySetAdminPassWordAttempt(short Index, byte cAttempt);
    private native int VikeyGetUserPassWordAttempt(short Index, byte[] pcAttempt);
    private native int VikeyGetAdminPassWordAttempt(short Index, byte[] pcAttempt);

    private native int VikeyResetPassword(short Index, byte[] NewUserPassword, byte[] NewAdminPassword);

    private native int ViKeySetSoftIDString(short Index, byte[] pSoftIDString);
    private native int ViKeyGetSoftIDString(short Index, byte[] pSoftIDString);

    private native int ViKeyGetUpdateTag(short Index, int[] pdwUpdateTag);
    private native int ViKeySetUpdateTag(short Index, int dwUpdateTag);

    private native int ViKeyGetVersionFlag(short Index, int[] pdwVersionFlag);
    private native int ViKeySetVersionFlag(short Index, int dwVersionFlag);

    private native int ViKeyReadData(short Index, short Addr, short Length, byte[] buffer);
    private native int ViKeyWriteData(short Index, short Addr, short Length, byte[] buffer);
    private native int ViKeyRandom(short Index, short[] pwRandom1, short[] pwRandom2, short[] pwRandom3, short[] pwRandom4);
    
	private native int ViKeyDecraseModule(short Index, short wModuleIndex);
    private native int ViKeyGetModule(short Index, short wModuleIndex, short[] pwValue);
    private native int ViKeySetModule(short Index, short wModuleIndex, short wValue, short wMode);
    private native int ViKeyCheckModule(short Index, short wModuleIndex, short[] IsZero, short[] CanDecrase);

	
    private native int ViKeySetMaxClientCount(short Index, short dwCount);
    private native int ViKeyGetMaxClientCount(short Index, short[] pdwCount);

    private native int ViKeySetMD5Key(short Index, byte[] pMD5key);
    private native int ViKeyHmacMD5(short Index, short length, byte[] pText, byte[] pResult); 
	
	private native int VikeyGetTime(short Index, byte[] pTime);
	
	public int Find(int[] lpdwCount){ return ViKeyFind(lpdwCount); }
	public int GetType(short Index, byte[] pType){ return ViKeyGetType(Index, pType); }
	public int GetHID(short index, int[] lpdwHID) { return ViKeyGetHID(index, lpdwHID);}
	
	
    public int GetLevel(short Index, byte[] pLevel) { return VikeyGetLevel(Index, pLevel);}
    public int UserLogin(short Index, byte[] pPassWord){ return ViKeyUserLogin(Index, pPassWord);}
    public int AdminLogin(short Index,  byte[] pPassWord){ return ViKeyAdminLogin(Index, pPassWord);}
    public int Logoff(short Index){ return ViKeyLogoff(Index);}

    public int SetUserPassWordAttempt(short Index, byte cAttempt){ return VikeySetUserPassWordAttempt(Index, cAttempt);}
    public int SetAdminPassWordAttempt(short Index, byte cAttempt){ return VikeySetAdminPassWordAttempt(Index, cAttempt);}
    public int GetUserPassWordAttempt(short Index, byte[] pcAttempt){ return VikeyGetUserPassWordAttempt(Index, pcAttempt);}
    public int GetAdminPassWordAttempt(short Index, byte[] pcAttempt){ return VikeyGetAdminPassWordAttempt(Index, pcAttempt);}

    public int ResetPassword(short Index, byte[] NewUserPassword, byte[] NewAdminPassword){ return VikeyResetPassword(Index, NewUserPassword, NewAdminPassword);}

    public int SetSoftIDString(short Index, byte[] pSoftIDString){ return ViKeySetSoftIDString(Index, pSoftIDString);}
    public int GetSoftIDString(short Index, byte[] pSoftIDString){ return ViKeyGetSoftIDString(Index, pSoftIDString);}

    public int GetUpdateTag(short Index, int[] pdwUpdateTag){ return ViKeyGetUpdateTag(Index, pdwUpdateTag);}
    public int SetUpdateTag(short Index, int dwUpdateTag){ return ViKeySetUpdateTag(Index, dwUpdateTag);}

    public int GetVersionFlag(short Index, int[] pdwVersionFlag){ return ViKeyGetVersionFlag(Index, pdwVersionFlag);}
    public int SetVersionFlag(short Index, int dwVersionFlag){ return ViKeySetVersionFlag(Index, dwVersionFlag);}

    public int ReadData(short Index, short Addr, short Length, byte[] buffer){ return ViKeyReadData(Index, Addr, Length, buffer);}
    public int WriteData(short Index, short Addr, short Length, byte[] buffer){ return ViKeyWriteData(Index, Addr, Length, buffer);}
    public int Random(short Index, short[] pwRandom1, short[] pwRandom2, short[] pwRandom3, short[] pwRandom4){ return ViKeyRandom(Index, pwRandom1, pwRandom2, pwRandom3, pwRandom4);}
    
	public int DecraseModule(short Index, short wModuleIndex){ return ViKeyDecraseModule(Index, wModuleIndex);}
    public int GetModule(short Index, short wModuleIndex, short[] pwValue){ return ViKeyGetModule(Index, wModuleIndex, pwValue);}
    public int SetModule(short Index, short wModuleIndex, short wValue, short wMode){ return ViKeySetModule(Index, wModuleIndex, wValue, wMode);}
    public int CheckModule(short Index, short wModuleIndex, short[] IsZero, short[] CanDecrase){ return ViKeyCheckModule(Index, wModuleIndex, IsZero, CanDecrase);}

	
    public int SetMaxClientCount(short Index, short dwCount){ return ViKeySetMaxClientCount(Index, dwCount);}
    public int GetMaxClientCount(short Index, short[] pdwCount){ return ViKeyGetMaxClientCount(Index, pdwCount);}

    public int SetMD5Key(short Index, byte[] pMD5key){ return ViKeySetMD5Key(Index, pMD5key);}
    public int HmacMD5(short Index, short length, byte[] pText, byte[] pResult){ return ViKeyHmacMD5(Index, length, pText, pResult);}
	
	public int GetTime(short Index, byte[] pTime){ return VikeyGetTime(Index, pTime);}
	
	
	
	public static void main(String args[])
	{
		ViKeyJavaObj test = new ViKeyJavaObj();
		short	Index = 0;
		long	retval;
		int[]	dwCount=new int[1];
		int[]	HID= new int[1];
		short	Addr;
		short	Length;
		byte[]  buffer=new byte[1024];
		byte[]  UserPassWord	=new byte[10];
		byte[]  AdminPassWord	=new byte[10];
		byte[]  SoftIDString 	=new byte[10];
		byte[]  szTime 	=new byte[10];


		retval = test.Find(dwCount);
		if (retval == 0)
		{
			System.out.println("系统中找到ViKey加密狗数量:"+dwCount[0]);
		}
		else
		{
			System.out.println("系统中没有找到ViKey加密狗");
			test.Logoff(Index);
			return;
		}
		
		Index = 0;
		//获取加密狗硬件ID
		retval = test.GetHID(Index, HID);
		if (retval == 0)
		{
			System.out.println("获取加密狗的硬件ID:"+HID[0]);
		}
		else
		{
			System.out.println("获取加密狗硬件ID错误");
			test.Logoff(Index);
			return;
		}
		
		UserPassWord[0] = 0x30;
		UserPassWord[1] = 0x30;
		UserPassWord[2] = 0x30;
		UserPassWord[3] = 0x30;
		UserPassWord[4] = 0x30;
		UserPassWord[5] = 0x30;
		UserPassWord[6] = 0x30;
		UserPassWord[7] = 0x30;
		UserPassWord[8] = 0;
		retval = test.AdminLogin(Index, UserPassWord);
		if (retval == 0)
		{
			System.out.println("用户登录加密狗成功!");
		}
		else
		{
			System.out.println("用户登录加密狗失败!");
			test.Logoff(Index);
			return;
		}
		
		
		SoftIDString[0] = '1';
		SoftIDString[1] = '2';
		SoftIDString[2] = '3';
		SoftIDString[3] = '4';
		SoftIDString[4] = '5';
		SoftIDString[5] = '6';
		SoftIDString[6] = '7';
		SoftIDString[7] = '8';
		SoftIDString[8] = 0;

		retval = test.SetSoftIDString(Index, SoftIDString);
		if (retval == 0)
		{
			System.out.println("设置加密狗软件ID成功!");
		}
		else
		{
			System.out.println("设置加密狗软件ID失败!");
			test.Logoff(Index);
			return;
		}

		
		retval = test.GetSoftIDString(Index, SoftIDString);
		if (retval == 0)
		{
			System.out.println("获取加密狗软件ID成功!");
		}
		else
		{
			System.out.println("获取加密狗软件ID失败!");
			test.Logoff(Index);
			return;
		}
	
		Addr = 0;
		Length = 10;
		for(byte m=0;m<10;m++) buffer[m] = m;	
		retval = test.WriteData(Index, Addr, Length, buffer);
		if (retval == 0)
		{
			System.out.println("向加密狗内写入数据成功");
		}
		else
		{
			System.out.println("向加密狗内写入数据失败!");
			test.Logoff(Index);
			return;
		}

		retval = test.ReadData(Index, Addr, Length, buffer);
		if (retval == 0)
		{
			System.out.println("从加密狗内读取数据成功");
		}
		else
		{
			System.out.println("从加密狗内读取数据失败!");
			test.Logoff(Index);
			return;
		}
		
		retval = test.GetTime(Index, szTime);
		if (retval == 0)
		{
			System.out.println("从加密狗内读取时间成功:"+szTime[0]+"年"+szTime[1]+"月"+szTime[2]+"日"+szTime[3]+"时"+szTime[4]+"分"+szTime[5]+"秒");
		}
		else
		{
			System.out.println("从加密狗内读取时间失败!");
			test.Logoff(Index);
			return;
		}

		retval = test.Logoff(Index);
		if (retval == 0)
		{
			System.out.println("关闭加密狗成功");
		}
		else
		{
			System.out.println("关闭加密狗失败!");
			return;
		}

	}

}
