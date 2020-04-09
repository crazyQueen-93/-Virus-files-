#include <Windows.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    FILE *f = NULL;
    int i;
    char *pBuffer = NULL;
    long lSize;
    int iKeySize;
    char szKey[] = "!asDPSk!@sakkf#!@kskdk12#@!#231saad2asdsD"; //key giai ma
    char szOutPut[MAX_PATH] = { '\0' };

    if ((argc < 2) || (argc > 3))
    {
        printf("Usage: Decode <Encrypted> <Result>");
        exit(1);
    }

    if (argc == 2)
    {
        strcpy(szOutPut, "Decoded.txt");
    }
    else
    {
        strncpy(szOutPut, argv[2], MAX_PATH);
    }

    f = fopen(argv[1], "rb"); //doc file da ma hoa
    if (f)
    {
        fseek(f, 0, SEEK_END);
        lSize = ftell(f);
        fseek(f, 0, SEEK_SET);
        pBuffer = new char[lSize];
        if (pBuffer)
        {
            fread((char *)pBuffer, lSize, 1, f);
            iKeySize = lstrlenA(szKey);
            for (i = 0; i < lSize; ++i)
            {
                pBuffer[i] ^= szKey[(i % iKeySize + 1) % iKeySize ]; //giai ma file
            }
        }
        fclose(f);
        if (pBuffer)
        {
            f = fopen(szOutPut, "wb");
            if (f)
            {
                fwrite((char *)pBuffer, lSize, 1, f); // ghi lai noi dung da giai ma
                fclose(f);
            }
            else
            {
                printf("Can not open output file.");
            }
            free(pBuffer);
        }
    }
    else
    {
        printf("Can not open input file.");
    }
    return 0;
}
