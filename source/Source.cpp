// @File source.cpp
// @Info Alleged RC4 encryption algorithm demo
// @Version 3.0
// @Aurthor Ben a.k.a DreamVB

#include <iostream>
#include "arc4.h"

using namespace std;

int main(int argc, char* argv[]){
	int klen;
	std::string file1;
	std::string file2;
	std::string pass;

	//Check command args
	if (argc != 4){
		std::cout << "USE: " << argv[0] <<
			" inputfile outputfile password" << std::endl;
		exit(EXIT_FAILURE);
	}

	file1 = argv[1];
	file2 = argv[2];
	klen = strlen(argv[3]);

	TRc4File rc4file;
	//Init encryption key
	rc4file.rc4_init((unsigned char *)argv[3], klen);
	//Encrypt file.
	rc4file.EncryptFile(file1, file2);
	//Return to system.
	return EXIT_SUCCESS;
}