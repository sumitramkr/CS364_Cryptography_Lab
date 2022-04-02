#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *caesarenc(char * message,int key){
    int i=0;
      for(i = 0; message[i] != '\0'; i++)
    {
        char ch;
        ch = message[i];
        if(ch >= 'a' && ch <= 'z')
        {
            ch = ch + key;
            if(ch > 'z'){
                ch = ch - 'z' + 'a' - 1;
            }
            message[i] = ch;
        }
        
    }
    return message;
}

char *caesardc(char *cypher,int key){
    int i=0;
    //decryption
    for(i = 0; cypher[i] != '\0'; i++)
    {
        char ch;
        ch = cypher[i];
        if(ch >= 'a' && ch <= 'z')
        {
            ch = ch - key;
            if(ch < 'a'){
                ch = ch + 'z' - 'a' + 1;
                }
            cypher[i] = ch;
        }
        
    }
    return cypher;
}

int main () {
    char message[512], ch;
    int i, key = 3;
    
    printf("Enter a message to encrypt: ");
    gets(message);
    char *cypher=caesarenc(message,key);
    
    printf("Encrypted Plain text from Caesar Cipher: %s", cypher);
    
    char *enc=caesardc(cypher,key);
    
printf("\nDecrypted text from Caesar Cipher: %s",enc);

    return 0;
}