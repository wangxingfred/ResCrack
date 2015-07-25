
#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>

#include "error.h"
#include "BinFile.h"
#include "PackParser.h"

using namespace std;

int main(int argc, const char * args[])
{
	ParseError error = E_SUCCESS;

	// ��ȡ�ļ�����
	string fileName;
	if (argc >= 2) {
		fileName = string(args[1]);
		cout << "fileName = " << fileName << endl;
	}

	BinFile binFile(fileName);

	// �ж��ļ��Ƿ����
	if (!binFile.exist()) {
		error = E_FILE_NOT_EXIST;
	}

	// �ж��ļ��Ƿ�Ϊ��
	if (error == E_SUCCESS && binFile.size() <= 0) {
		error = E_FILE_EMPTY;
	}

	// �����ļ�
	if (error == E_SUCCESS) {
		error = binFile.load();
	}

	// �����ļ�
	if (error == E_SUCCESS) {
		PackParser parser;
		//error = parser.parse(binFile);
		error = parser.bytesOperation(binFile);
	}

	if (error != E_SUCCESS) {
		cout << "error = " << error 
			<< "\ndes = " << Util::getInstance()->getLastError()
			<< "\nsize = " << binFile.size()
			<< endl;
		return error;
	}

	cout << " ## SUCCESS ## " << endl;

	return E_SUCCESS;
}