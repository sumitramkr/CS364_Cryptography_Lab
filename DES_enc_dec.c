//lab assignment 2
//sumitram kumar
//201951156

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char BYTE;

BYTE KEYY[8];
BYTE G_DATA[8];

BYTE P1[7];
BYTE SECRET_KEY[16][7];
BYTE P2[16][6];
BYTE I_P[8];
BYTE EP[6];
BYTE S_B[8];
BYTE S_P[4];
BYTE E_D[8];

BYTE L_S[] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

void Permute(BYTE *DES, const BYTE *Keyy, const BYTE *ind, int bts) {
    int i, j, kBit, kByte, dBit, dByte;

    for (i = 0; i < bts; ++i) {
        j = ind[i] - 1;
        kBit = j % 8;
        kByte = j / 8;

        dBit = i % 8;
        dByte = i / 8;

        if (Keyy[kByte] & (1 << kBit))
            DES[dByte] |= (1 << dBit);
        else
            DES[dByte] &= ~(1 << dBit);
    }
}

void GenerateSubKeys(BYTE *SECRET_KEY, BYTE *DES) {
    int i;

    for (i = 0; i < 16; ++i) {
        int bts = L_S[i];
        BYTE n;
        int i, c, cc1, cc2;

        while (bts-- > 0) {
            cc1 = DES[0] & 1;
            cc2 = DES[3] & 0x10;

            c = cc2;
            for (i = 6; i >= 0; --i) {
                n = (DES[i] >> 1);
                if (c)
                    n |= 0x80;
                c = DES[i] & 1;
                DES[i] = n;
            }
            DES[3] &= ~0x08;
            if (cc1)
                DES[3] |= 0x08;
        }
        memcpy(SECRET_KEY + 7 * i, DES, 7);
    }
}


int main(int argc, char *argv[]) {

    int GetBit(BYTE *BFR, int IND) {
        int bit = BFR[IND / 8] & (1 << (IND % 8));
        return bit ? 1 : 0;
    }

    BYTE c;
    static char buf[16];
    int i, j, k, b1, b2, b3, b4, n;

    if (argc < 3) {
        return 1;
    }

    if (strlen(argv[1]) != 16) {
        return 2;
    }

    if (strlen(argv[2]) != 16) {
        return 2;
    }

    for (i = 0; i < 8; ++i) {
        strncpy(buf, argv[1] + 2 * i, 2);
        KEYY[i] = (BYTE) strtoul(buf, NULL, 16);
    }

    for (i = 0; i < 8; ++i) {
        strncpy(buf, argv[2] + 2 * i, 2);
        G_DATA[i] = (BYTE) strtoul(buf, NULL, 16);
    }

    BYTE PC1_Index[] = {

            57, 49, 41, 33, 25, 17, 9,
            1, 58, 50, 42, 34, 26, 18,
            10, 2, 59, 51, 43, 35, 27,
            19, 11, 3, 60, 52, 44, 36,
            63, 55, 47, 39, 31, 23, 15,
            7, 62, 54, 46, 38, 30, 22,
            14, 6, 61, 53, 45, 37, 29,
            21, 13, 5, 28, 20, 12, 4,

    };

    Permute(P1, KEYY, PC1_Index, 56);

    printf("key --> ");
    for (i = 0; i < 8; ++i)
        printf("%02X", KEYY[i]);
    printf("\n");

    printf("plain text --> ");
    for (i = 0; i < 8; ++i)
        printf("%02X", G_DATA[i]);
    printf("\n");

    GenerateSubKeys(SECRET_KEY[0], P1);

    BYTE PC2_Index[] = {

            14, 17, 11, 24, 1, 5,
            3, 28, 15, 6, 21, 10,
            23, 19, 12, 4, 26, 8,
            16, 7, 27, 20, 13, 2,
            41, 52, 31, 37, 47, 55,
            30, 40, 51, 45, 33, 48,
            44, 49, 39, 56, 34, 53,
            46, 42, 50, 36, 29, 32,

    };

    for (i = 0; i < 16; ++i)
        Permute(P2[i], SECRET_KEY[i], PC2_Index, 48);

    BYTE IP_Index[] = {

            58, 50, 42, 34, 26, 18, 10, 2,
            60, 52, 44, 36, 28, 20, 12, 4,
            62, 54, 46, 38, 30, 22, 14, 6,
            64, 56, 48, 40, 32, 24, 16, 8,
            57, 49, 41, 33, 25, 17, 9, 1,
            59, 51, 43, 35, 27, 19, 11, 3,
            61, 53, 45, 37, 29, 21, 13, 5,
            63, 55, 47, 39, 31, 23, 15, 7,

    };

    Permute(I_P, G_DATA, IP_Index, 64);

    BYTE EXP_Index[] = {

            32, 1, 2, 3, 4, 5,
            4, 5, 6, 7, 8, 9,
            8, 9, 10, 11, 12, 13,
            12, 13, 14, 15, 16, 17,
            16, 17, 18, 19, 20, 21,
            20, 21, 22, 23, 24, 25,
            24, 25, 26, 27, 28, 29,
            28, 29, 30, 31, 32, 1,

    };

    BYTE S_Index[8][4][16] = {

            14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
            0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
            4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
            15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13,

            15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
            3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
            0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
            13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9,

            10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
            13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
            13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
            1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12,

            7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
            13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
            10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
            3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14,

            2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
            14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
            4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
            11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3,

            12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
            10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
            9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
            4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13,

            4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
            13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
            1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
            6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12,

            13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
            1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
            7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
            2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11

    };

    BYTE P_Index[] = {

            16, 7, 20, 21,
            29, 12, 28, 17,
            1, 15, 23, 26,
            5, 18, 31, 10,
            2, 8, 24, 14,
            32, 27, 3, 9,
            19, 13, 30, 6,
            22, 11, 4, 25

    };

    //encryption phase

    for (n = 0; n < 16; ++n) {
        Permute(EP, I_P + 4, EXP_Index, 48);

        for (i = 0; i < 6; ++i)
            EP[i] ^= P2[n][i];

        memset(S_B, '\0', 4);
        for (i = 0; i < 8; ++i) {
            b1 = GetBit(EP, 6 * i);
            b2 = GetBit(EP, 6 * i + 5);
            j = (b1 << 1) | b2;

            b1 = GetBit(EP, 6 * i + 1);
            b2 = GetBit(EP, 6 * i + 2);
            b3 = GetBit(EP, 6 * i + 3);
            b4 = GetBit(EP, 6 * i + 4);
            k = (b1 << 3) | (b2 << 2) | (b3 << 1) | b4;

            c = S_Index[i][j][k];
            S_B[i >> 1] |= (i & 1) ? c << 4 : c;
        }

        Permute(S_P, S_B, P_Index, 32);

        for (i = 0; i < 4; ++i)
            S_P[i] ^= I_P[i];

        memcpy(I_P, I_P + 4, 4);
        memcpy(I_P + 4, S_P, 4);
    }

    BYTE F_Index[] = {

            40, 8, 48, 16, 56, 24, 64, 32,
            39, 7, 47, 15, 55, 23, 63, 31,
            38, 6, 46, 14, 54, 22, 62, 30,
            37, 5, 45, 13, 53, 21, 61, 29,
            36, 4, 44, 12, 52, 20, 60, 28,
            35, 3, 43, 11, 51, 19, 59, 27,
            34, 2, 42, 10, 50, 18, 58, 26,
            33, 1, 41, 9, 49, 17, 57, 25

    };

    Permute(E_D, I_P, F_Index, 64);

    printf("cipher text --> ");
    for (i = 0; i < 8; ++i)
        printf("%02X", E_D[i]);
    printf("\n");

    printf("\n");

    //decryption phase
    for (n = 0; n < 16; ++n) {
        Permute(EP, I_P, EXP_Index, 48);

        for (i = 0; i < 6; ++i)
            EP[i] ^= P2[15 - n][i];

        memset(S_B, '\0', 4);
        for (i = 0; i < 8; ++i) {
            b1 = GetBit(EP, 6 * i);
            b2 = GetBit(EP, 6 * i + 5);
            j = (b1 << 1) | b2;

            b1 = GetBit(EP, 6 * i + 1);
            b2 = GetBit(EP, 6 * i + 2);
            b3 = GetBit(EP, 6 * i + 3);
            b4 = GetBit(EP, 6 * i + 4);
            k = (b1 << 3) | (b2 << 2) | (b3 << 1) | b4;

            c = S_Index[i][j][k];
            S_B[i >> 1] |= (i & 1) ? c << 4 : c;
        }

        Permute(S_P, S_B, P_Index, 32);

        for (i = 0; i < 4; ++i)
            S_P[i] ^= I_P[i + 4];

        memcpy(I_P + 4, I_P, 4);
        memcpy(I_P, S_P, 4);
    }

    Permute(E_D, I_P, F_Index, 64);

    printf("decrypted text --> ");
    for (i = 0; i < 8; ++i)
        printf("%02X", E_D[i]);
    printf("\n");

    printf("\n");

    return 0;
}
