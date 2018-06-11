//#ifndef VIKEY_API
//#define VIKEY_API

typedef enum 
{
	ViKeyAPP = 0,						
	ViKeySTD = 1,						
	ViKeyNET = 2,						
	ViKeyPRO = 3,						
	ViKeyWEB = 4,						
	ViKeyTIME = 5,						
	ViKeyMultiFunctional = 0x0A,		
	ViKeyMultiFunctionalTime = 0x0B,	
	ViKeyInvalid	

} VikeyType;


#define ViKeyNoLevel		0	//ÄäÃûÈšÏÞ(Ã»ÓÐµÇÂŒ¹ýŒÓÃÜ¹·Ê±£¬ŽËÊ±ÈšÏÞÎªÄäÃûÈšÏÞ)
#define ViKeyUserLevel		1	//ÓÃ»§ÈšÏÞ(µ÷ÓÃVikeyUserLoginµÇÂŒŒÓÃÜ¹·³É¹Šºó£¬ŽËÊ±ÈšÏÞÎªÓÃ»§ÈšÏÞ)
#define ViKeyAdminLevel		2	//¹ÜÀíÔ±ÈšÏÞ(µ÷ÓÃVikeyAdminLoginµÇÂŒŒÓÃÜ¹·³É¹Šºó£¬ŽËÊ±ÈšÏÞÎª¹ÜÀíÔ±ÈšÏÞ)

#define VIKEY_SUCCESS						0x00000000 //³É¹Š
#define VIKEY_ERROR_NO_VIKEY				0x80000001 //Ã»ÓÐÕÒµœViKeyŒÓÃÜËø
#define VIKEY_ERROR_INVALID_PASSWORD		0x80000002 //ÃÜÂëŽíÎó
#define VIKEY_ERROR_NEED_FIND				0x80000003 //ÇëÏÈ²éÕÒŒÓÃÜËø
#define VIKEY_ERROR_INVALID_INDEX			0x80000004 //ÎÞÐ§µÄŸä±ú
#define VIKEY_ERROR_INVALID_VALUE			0x80000005 //ÊýÖµŽíÎó
#define VIKEY_ERROR_INVALID_KEY				0x80000006 //ÃØÔ¿ÎÞÐ§
#define VIKEY_ERROR_GET_VALUE				0x80000007 //¶ÁÈ¡ÐÅÏ¢ŽíÎó
#define VIKEY_ERROR_SET_VALUE				0x80000008 //ÉèÖÃÐÅÏ¢ŽíÎó
#define VIKEY_ERROR_NO_CHANCE				0x80000009 //Ã»ÓÐ»ú»á
#define VIKEY_ERROR_NO_TAUTHORITY			0x8000000A //ÈšÏÞ²»×ã
#define VIKEY_ERROR_INVALID_ADDR_OR_SIZE	0x8000000B //µØÖ·»ò³€¶ÈŽíÎó
#define VIKEY_ERROR_RANDOM					0x8000000C //»ñÈ¡Ëæ»úÊýŽíÎó
#define VIKEY_ERROR_SEED					0x8000000D //»ñÈ¡ÖÖ×ÓŽíÎó
#define VIKEY_ERROR_CONNECTION				0x8000000E //ÍšÐÅŽíÎó
#define VIKEY_ERROR_CALCULATE				0x8000000F //Ëã·š»òŒÆËãŽíÎó
#define VIKEY_ERROR_MODULE					0x80000010 //ŒÆÊýÆ÷ŽíÎó
#define VIKEY_ERROR_GENERATE_NEW_PASSWORD	0x80000011 //²úÉúÃÜÂëŽíÎó
#define VIKEY_ERROR_ENCRYPT_FAILED			0x80000012 //ŒÓÃÜÊýŸÝŽíÎó
#define VIKEY_ERROR_DECRYPT_FAILED			0x80000013 //œâÃÜÊýŸÝŽíÎó
#define VIKEY_ERROR_ALREADY_LOCKED			0x80000014 //ViKeyŒÓÃÜËøÒÑŸ­±»Ëø¶š
#define VIKEY_ERROR_UNKNOWN_COMMAND			0x80000015 //ÎÞÐ§µÄÃüÁî
#define VIKEY_ERROR_NO_SUPPORT				0x80000016 //µ±Ç°ViKeyŒÓÃÜËø²»Ö§³ÖŽË¹ŠÄÜ
#define VIKEY_ERROR_UNKNOWN_ERROR			0xFFFFFFFF //ÎŽÖªŽíÎó

#ifdef __cplusplus
extern "C"{
#endif

/*********For ViKeyAPP¡¢ViKeySTD¡¢ViKeyNet¡¢ViKeyPRO¡¢ViKeyTime APIs**********/

DWORD VikeyFind(DWORD* pdwCount);
DWORD VikeyGetHID(WORD Index, DWORD *pdwHID);
DWORD VikeyGetType(WORD Index, VikeyType * pType);
DWORD VikeyGetLevel(WORD Index, BYTE *pLevel);
DWORD VikeySetPtroductName(WORD Index, WCHAR szName[16]);
DWORD VikeyGetPtroductName(WORD Index, WCHAR szName[16]);

//µÇÂœ¡¢×¢ÏúŒÓÃÜ¹·
//ŒÓÃÜ¹·ÃÜÂë³€¶È8žö×Ö·û ×ÖÄž»òÊý×Ö
DWORD VikeyUserLogin(WORD Index, char * pUserPassWord);
DWORD VikeyAdminLogin(WORD Index, char * pAdminPassWord);
DWORD VikeyLogoff(WORD Index);

//ÉèÖÃÃÜÂë³¢ÊÔŽÎÊý¡¢ÐÞžÄÃÜÂë
DWORD VikeySetUserPassWordAttempt(WORD Index, BYTE cAttempt);
DWORD VikeySetAdminPassWordAttempt(WORD Index, BYTE cAttempt);
DWORD VikeyGetUserPassWordAttempt(WORD Index, BYTE *pcCurrentAttempt, BYTE *pcMaxAttempt);
DWORD VikeyGetAdminPassWordAttempt(WORD Index, BYTE *pcCurrentAttempt, BYTE *pcMaxAttempt);
DWORD VikeyResetPassword(WORD Index, char * pNewUserPassWord, char * pNewAdminPassWord);

//ÈíŒþID¶ÁÐŽ
//ÈíŒþID³€¶È8žö×Ö·û ×ÖÄž»òÊý×Ö
DWORD VikeySetSoftIDString(WORD Index, char * pSoftIDString);
DWORD VikeyGetSoftIDString(WORD Index, char * pSoftIDString);

//¶ÁÐŽÊýŸÝ
DWORD VikeyReadData(WORD Index, WORD Addr, WORD Length, BYTE * buffer);
DWORD VikeyWriteData(WORD Index, WORD Addr, WORD Length, BYTE * buffer);
DWORD ViKeyRandom(WORD Index, WORD* pwRandom1, WORD* pwRandom2, WORD* pwRandom3, WORD* pwRandom4);
DWORD VikeySeed(WORD Index, DWORD dwSeed, WORD* pwData1, WORD* pwData2, WORD* pwData3, WORD* pwData4);

//ŒÆÊýÆ÷Ä£¿é
DWORD ViKeyDecraseModule(WORD Index, WORD wModuleIndex);
DWORD ViKeyGetModule(WORD Index, WORD wModuleIndex, WORD* pwValue);
DWORD ViKeySetModule(WORD Index, WORD wModuleIndex, WORD wValue, WORD wMode);
DWORD ViKeyCheckModule(WORD Index, WORD wModuleIndex, WORD *IsZero, WORD* CanDecrase);

//ŒÓœâÃÜ

typedef enum 
{
	Des3KeyLength16,
	Des3KeyLength24
}Des3KeyLengthType;

DWORD Vikey3DesSetKey(WORD Index, BYTE * pKey, Des3KeyLengthType KeyType);
DWORD Vikey3DesEncrypt(WORD Index, WORD length, BYTE * pText, BYTE* pResult);
DWORD Vikey3DesDecrypt(WORD Index, WORD length, BYTE * pText, BYTE* pResult);

//For ViKeyNET¡¢ViKeyPRO
DWORD VikeySetMaxClientCount(WORD Index, WORD dwCount);
DWORD VikeyGetMaxClientCount(WORD Index, WORD* pdwCount);

//For ViKeyWEB¡¢ViKeyPRO
DWORD VikeyMD5(WORD Index, WORD length, BYTE * pText, BYTE* pResult);
DWORD VikeySetMD5Key(WORD Index, BYTE * pMD5key);
DWORD VikeyHmacMD5(WORD Index, WORD length, BYTE * pText, BYTE* pResult);

DWORD VikeySHA1(WORD Index, WORD length, BYTE * pText, BYTE* pResult);
DWORD VikeySetSHA1Key(WORD Index, BYTE * pSHA1key);
DWORD VikeyHmacSHA1(WORD Index, WORD length, BYTE * pText, BYTE* pResult);


//For ViKeyTIME
//»ñÈ¡Ê±ÖÓÐÍŒÓÃÜ¹·ÖÐµÄÄÚ²¿Ê±Œä
DWORD VikeyGetTime(WORD Index, BYTE* pTime);

#ifdef __cplusplus
} //  extern "C"{
#endif

//#endif
