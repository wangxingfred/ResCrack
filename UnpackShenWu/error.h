
#ifndef __INCLUDE_ERROR_H__
#define __INCLUDE_ERROR_H__

enum ParseError
{
	E_SUCCESS,				// 成功
	E_FILE_NOT_EXIST,		// 文件不存在
	E_FILE_EMPTY,			// 文件为空
	E_FILE_CREATE_FAILED,	// 文件创建失败
	E_MEM_LOC_FAILED,		// 内存分配失败
	E_READ_INCOMPELETE,		// 读取不全
	E_STRING_NOT_FOUND,		// 字符串找不到
	E_XML_HEAD_NOT_FOUND,	// XML头找不到
	E_XML_TAIL_NOT_FOUND,	// XML尾找不到
	E_PNG_HEAD_NOT_FOUND,	// PNG头找不到
	E_PNG_TAIL_NOT_FOUND	// PNG尾找不到
};

#endif