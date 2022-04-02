#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int pMod(int num, int mod)
{
    return (num % mod + mod) % mod;
}
//encryption
char *encryptAffine(int alpha, int beta, char *plainText)
{
    int len = strlen(plainText);
    char *encryptedText = (char *)malloc(len + 1);
    for (size_t i = 0; i < len; i++)
    {
        // encrypting using (alpha*x + beta) % 26
        int shiftAlpha = (((alpha * (plainText[i] - 'a')) + beta) % 26);
        encryptedText[i] = (char)(shiftAlpha + 'a');
    }
    return encryptedText;
}

//decryption
char *decryptAffine(int alpha, int beta, char *encryptedText)
{
    int len = strlen(encryptedText);
    char *plainText = (char *)malloc(len + 1);

    int alphaInv;
    // finding a^-1
    for (size_t i = 0; i < 26; i++)
    {
        if ((alpha * i) % 26 == 1)
            alphaInv = i;
    }

    for (size_t i = 0; i < len; i++)
    {
        int shiftAlpha = pMod((encryptedText[i] - 'a' - beta) * alphaInv, 26);
        plainText[i] = (char)(shiftAlpha + 'a');
    }
    return plainText;
}

//Main/Test function
int main(int argc, char *argv[])
{
	//Function call
    int alpha = 7, beta = 5;
    char *c3 = encryptAffine(alpha, beta, c2);
    // Decrypting Affine Cipher
    char *decryptedC2 = decryptAffine(alpha, beta, c3)
	return 0;
}