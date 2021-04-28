// @File rc4.cpp
// @Info RC4 encryption algorithm
// @Version 3.0
// @Aurthor Ben a.k.a DreamVB

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
using namespace std;

const int KEY_LEN_MIN = 6;
const int KEY_LEN_MAX = 256;

unsigned char S[KEY_LEN_MAX];
int key_size = 0;

void rc4_init(unsigned char *key);
void set_message(char *msg);

void set_message(char *msg){
	std::cout << msg << std::endl;
}

void rc4_init(unsigned char *key) {
	unsigned int j = 0;

	//Init S with 0..255
	for (unsigned int x = 0; x < KEY_LEN_MAX; x++){
		S[x] = (unsigned char)x;
	}

	//KSA
	for (unsigned int x = 0; x < KEY_LEN_MAX; x++){
		j = (j + S[x] + key[x % key_size]) % KEY_LEN_MAX;
		//Swap the values in the S array
		std::swap(S[x], S[j]);
	}
}

int main(int argc, char* argv[]){
	fstream fin;
	fstream fout;
	char ch;
	unsigned char k;
	unsigned int a = 0;
	unsigned int b = 0;

	//Check command args
	if (argc != 4){
		std::cout << "USE: " << argv[0] << " inputfile outputfile password" << std::endl;
		exit(EXIT_FAILURE);
	}
	//Get key length
	key_size = strlen(argv[3]);

	if (key_size < KEY_LEN_MIN){
		std::cout << "The password is too short." << std::endl <<
			"Password needs to be at least 6 characters long." << std::endl;
		exit(EXIT_FAILURE);
	}
	//Check less is not above 256
	if (key_size > KEY_LEN_MAX){
		std::cout << "Encryption key needs to be less or equal to 256 characters." << std::endl;
		exit(EXIT_FAILURE);
	}
	//Set display message
	set_message("Preparing to open and write files.");

	//Open input file for reading.
	fin.open(argv[1], std::ios::in | std::ios::binary);

	//Check if the file was opened.
	if (!fin.is_open()){
		std::cout << "Failed to open file." << 
			std::endl << argv[1] << std::endl;
		exit(EXIT_FAILURE);
	}

	//Open output file.
	fout.open(argv[2], std::ios::out | std::ios::binary);

	//Check if file was opened.
	if (!fout.good()){
		std::cout << "Failed to open destination file." << std::endl 
			<< argv[2] << std::endl;
		fin.close();
		exit(EXIT_FAILURE);
	}

	//Setup encryption key
	rc4_init((unsigned char *)argv[3]);
	//Set display message
	set_message("Initializing the RC4 Key.");
	//Set display message
	set_message("Starting file encryption phase.");

	if (fout.is_open()){
		//Get byte
		fin.get(ch);
		//Loop till end of file.
		while (!fin.eof()){
			//Do encryption
			a = (a + 1) % KEY_LEN_MAX;
			b = (b + S[a]) % KEY_LEN_MAX;
			std::swap(S[a], S[b]);
			k = S[(S[a] + S[b]) % 256] ^ ch;
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
	set_message("Finished ....exiting");
	return EXIT_SUCCESS;
}