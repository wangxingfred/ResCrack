
#ifndef __INCLUDE_ERROR_H__
#define __INCLUDE_ERROR_H__

enum ParseError
{
	E_SUCCESS,				// �ɹ�
	E_FILE_NOT_EXIST,		// �ļ�������
	E_FILE_EMPTY,			// �ļ�Ϊ��
	E_FILE_CREATE_FAILED,	// �ļ�����ʧ��
	E_MEM_LOC_FAILED,		// �ڴ����ʧ��
	E_READ_INCOMPELETE,		// ��ȡ��ȫ
	E_STRING_NOT_FOUND,		// �ַ����Ҳ���
	E_XML_HEAD_NOT_FOUND,	// XMLͷ�Ҳ���
	E_XML_TAIL_NOT_FOUND,	// XMLβ�Ҳ���
	E_PNG_HEAD_NOT_FOUND,	// PNGͷ�Ҳ���
	E_PNG_TAIL_NOT_FOUND	// PNGβ�Ҳ���
};

#endif