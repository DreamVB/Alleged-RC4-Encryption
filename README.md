# Alleged RC4 encryption algorithm
Example showing how to encrypt files with the rc4 algorithm

This version comes as a class to easy plug into your programs.

# Using the class


```cpp
#include "arc4.h"

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
```
