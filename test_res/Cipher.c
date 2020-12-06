#include<stdio.h>
#include<stdlib.h>

char* caesar_cipher(char* plaintext) {
	char* ciphertext = (char*)malloc(20);
	int i = 0;
	while (plaintext[i] != 0) {
		ciphertext[i] = plaintext[i] + 3;
		i += 1;
	}
	ciphertext[i] = 0;
	return ciphertext;
}

int main() {

	char plaintext[20];
	printf("Enter a word: ");
	scanf("%s", plaintext);
	
	char *ciphertext = caesar_cipher(plaintext);
	printf("%s\n", ciphertext);
	return 0;
}