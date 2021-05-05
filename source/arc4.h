// @File arc4.h
// @Info Alleged RC4 encryption algorithm
// @Version 3.0
// @Aurthor Ben a.k.a DreamVB

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
using namespace std;

class TRc4File{
private:
	const int KEY_LEN_MIN = 6;
	const int KEY_LEN_MAX = 256;
	//SBox
	unsigned char S[256];
	int key_size = 0;

	void set_message(ostream &obj, int code){
		//Display process message.
		switch (code)
		{
		case 1:
			obj << "Preparing to open and write files." << std::endl;
			break;
		case 2:
			obj << "Initializing the RC4 Key." << std::endl;
			break;
		case 3:
			obj << "Starting file encryption phase." << std::endl;
			break;
		case 4:
			obj << "Finished ....exiting" << std::endl;
		default:
			break;
		}
	}

public:

	~TRc4File(){
		key_size = 0;
		memset(S, 0, sizeof S);
	}

	void rc4_init(unsigned char *key, int length) {
		unsigned int j = 0;

		this->key_size = length;

		//Init S with 0..255
		for (unsigned int x = 0; x < this->KEY_LEN_MAX; x++){
			this->S[x] = (unsigned char)x;
		}

		//KSA
		for (unsigned int x = 0; x < this->KEY_LEN_MAX; x++){
			j = (j + this->S[x] + key[x % this->key_size]) % this->KEY_LEN_MAX;
			//Swap the values in the S array
			std::swap(this->S[x], this->S[j]);
		}
	}

	void EncryptFile(std::string InputFile, std::string OutPutFile){
		fstream fin;
		fstream fout;
		char ch;
		unsigned char k;
		unsigned int a = 0;
		unsigned int b = 0;

		if (key_size < this->KEY_LEN_MIN){
			std::cout << "The password is too short." << std::endl <<
				"Password needs to be at least 6 characters long." << std::endl;
			exit(EXIT_FAILURE);
		}
		//Check less is not above 256
		if (key_size > this->KEY_LEN_MAX){
			std::cout << "Encryption key needs to be less or equal to 256 characters." << std::endl;
			exit(EXIT_FAILURE);
		}
		//Set display message
		set_message(std::cout,1);

		//Open input file for reading.
		fin.open(InputFile, std::ios::in | std::ios::binary);

		//Check if the file was opened.
		if (!fin.is_open()){
			std::cout << "Failed to open file." <<
				std::endl << InputFile.c_str() << std::endl;
			exit(EXIT_FAILURE);
		}

		//Open output file.
		fout.open(OutPutFile, std::ios::out | std::ios::binary);

		//Check if file was opened.
		if (!fout.good()){
			std::cout << "Failed to open destination file." << std::endl
				<< OutPutFile.c_str() << std::endl;
			fin.close();
			exit(EXIT_FAILURE);
		}
		//Set display message
		set_message(std::cout, 2);
		//Set display message
		set_message(std::cout, 3);

		if (fout.is_open()){
			//Get byte
			fin.get(ch);
			//Loop till end of file.
			while (!fin.eof()){
				//Do encryption
				a = (a + 1) % this->KEY_LEN_MAX;
				b = (b + this->S[a]) % this->KEY_LEN_MAX;
				std::swap(this->S[a], this->S[b]);
				k = this->S[(this->S[a] + this->S[b]) % this->KEY_LEN_MAX] ^ ch;
				//Write to output file.
				fout.put(k);
				//Get next byte
				fin.get(ch);
			}
		}
		//Close open files
		fout.close();
		fin.close();
		//Set display message
		set_message(std::cout, 4);
	}
};