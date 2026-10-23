#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

unsigned char enc_msg[] = { 0x17, 0x24, 0x2f, 0x3e, 0x28, 0x28, 0x05, 0x28, 0x3c, 0x3e, 0x3e, 0x3e, 0x28, 0x2f, 0x3c, 0x2e, 0x2b, 0x34, 0x66 };

void decrypt_str(unsigned char *data, int len) {
    for (int i = 0; i < len; i++) data[i] ^= 0x55;
}

int main() {
    decrypt_str(enc_msg, sizeof(enc_msg));
    char path[MAX_PATH];
    sprintf(path, "%s\\Desktop\\Defender_Bypassed.txt", getenv("USERPROFILE"));
    FILE *f = fopen(path, "w");
    if (f) { fprintf(f, "%s\n", enc_msg); fclose(f); }
    return 0;
}
