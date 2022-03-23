#include<stdio.h>
char ans[4];
char fun(char s){
    char temp=s;
    int g;
    if((temp>>7)==0){
       g=(s<<1);
    }
    else{
        g=(s<<1)^27;
    }
   return g;
}
int main(){
    char ch;
    char s[4][4]={
        0xf2,0x13, 0x53,0x45,
        0x0a,0x13, 0x53,0x45,
        0x22,0x13, 0x53,0x45,
        0x5c,0x13, 0x53,0x45
    };
    
    //scanf("%c",&ch);
    int i=0;
    s[0][0]=fun(s[0][0])^fun(s[1][0])^s[1][0]^s[2][0]^s[3][0];
    
    printf("%x\n",s[0][0]);
    
    
    
    return 0;
}