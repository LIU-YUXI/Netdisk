#define _CRT_NON_CONFORMING_SWPRINTFS
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<Windows.h>


using namespace std;
// ���ֽ��ַ���ת���ֽ��ַ���
void W2C(wchar_t* pwszSrc, int iSrcLen, char* pszDest, int iDestLen)
{
    ::RtlZeroMemory(pszDest, iDestLen);
    // ���ֽ��ַ���ת���ֽ��ַ���
    ::WideCharToMultiByte(CP_ACP,
        0,
        pwszSrc,
        (iSrcLen / 2),
        pszDest,
        iDestLen,
        NULL,
        NULL);
}
int main() {
	char dir[10] = "./test";
	HANDLE dir_handle = CreateFileA(dir, FILE_LIST_DIRECTORY, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL);

	if (dir_handle == INVALID_HANDLE_VALUE) {
		exit(0);
	}

	char szTemp[MAX_PATH] = { 0 };

	BOOL bRet = false;
	DWORD dwRet = 0;
	DWORD dwBufferSize = 2048;
	BYTE* pBuf = new BYTE[dwBufferSize];
	if (NULL == pBuf)
	{
		exit(0);
	}
    do
    {
        FILE_NOTIFY_INFORMATION* pFileNotifyInfo = (FILE_NOTIFY_INFORMATION*)pBuf;
        ::RtlZeroMemory(pFileNotifyInfo, dwBufferSize);
        // ���ü��Ŀ¼
        bRet = ::ReadDirectoryChangesW(dir_handle,
            pFileNotifyInfo,
            dwBufferSize,
            TRUE,
            FILE_NOTIFY_CHANGE_SIZE |  // in file or subdir
            FILE_NOTIFY_CHANGE_ATTRIBUTES |
            FILE_NOTIFY_CHANGE_DIR_NAME | // creating, deleting a directory or sub
            FILE_NOTIFY_CHANGE_FILE_NAME|
            FILE_NOTIFY_CHANGE_CREATION,
            //FILE_NOTIFY_CHANGE_LAST_WRITE,//������ر�����ᵼ��Ŀ¼�е��ļ���Ҳ��ʾ������
            &dwRet,
            NULL,
            NULL);
        if (FALSE == bRet)
        {
            exit(0);
            break;
        }
        
       
        // �жϲ������Ͳ���ʾ
        while (1) {
            // �����ַ�ת����խ�ַ�
            W2C((wchar_t*)(&pFileNotifyInfo->FileName), pFileNotifyInfo->FileNameLength, szTemp, MAX_PATH);
            switch (pFileNotifyInfo->Action)
            {
            case FILE_ACTION_ADDED:
            {
                // �����ļ�
                printf("[File Added Action]%s\n", szTemp);
                break;
            }
            case FILE_ACTION_REMOVED:
            {
                // �����ļ�
                printf("[File Removed Action]%s\n", szTemp);
                break;
            }
            case FILE_ACTION_MODIFIED:
            {
                // �����ļ�
                printf("[File Modified Action]%s\n", szTemp);
                break;
            }
            case FILE_ACTION_RENAMED_NEW_NAME:
            {
                printf("[File New Name]%s\n", szTemp);
                break;
            }
            case FILE_ACTION_RENAMED_OLD_NAME:
            {
                printf("[File Old Name]%s\n", szTemp);
                break;
            }
            default:
            {
                break;
            }
            }
            if (pFileNotifyInfo->NextEntryOffset != 0)//�ಽ�������ƶ�ƫ����
            {
                pFileNotifyInfo = (FILE_NOTIFY_INFORMATION*)(((BYTE*)pFileNotifyInfo) + pFileNotifyInfo->NextEntryOffset);
            }
            else
            {
                break;
            }
        }
    } while (bRet);

    ::CloseHandle(dir_handle);
    delete[] pBuf;
    pBuf = NULL;
    return 0;
} 