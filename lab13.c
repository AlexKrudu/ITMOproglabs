#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int text_fr_ind = 0, url_fr_ind = 0;
FILE *fin;

int GetSize(char* size, int bit);
void show();
int change(char* prop_name, char* prop_value);
int ShowOne(char* prop_name);
int MakeArguments(int argc, char* argv[], char* filename, char* command, char* prop_name, char* prop_value);

struct TagHeader{
    char identifier[3];
    short version;
    char flags;
    char size[4];

} hd;

struct FrameHeader{
    char id[4];
    char size[4];
    char flags[2];
} fr_hd;

struct Data{

    struct Text{
        char name[5];
        char* info;
        int size;
        long int pos;
    } text_frames[40];

    struct URL{
        char name[5];
        char* info;
        int size;
        long int pos;
    } url_frames[10];

    struct{
        char name[5];
        char* info;
        int size;
        char language[3];
        long int pos;
    } Comm;

} Info;

int main(int argc, char* argv[])
{
    int i;
    char filename[100] = "";
    char command[7] = "";
    char prop_name[5] = "";
    char prop_value[1000] = "";
    if(MakeArguments(argc, argv, filename, command, prop_name, prop_value) == 1){
        printf("Error! Wrong arguments!\n");
        getchar();
        return 1;
    }

    fin = fopen(filename, "r+b");
    if(fin == NULL){
        printf("Error! Can't open file!\n");
        getchar();
        return 1;
    }
    fread(hd.identifier, 1, 3, fin);
    fread(&hd.version, 2, 1, fin);
    fread(&hd.flags, 1, 1, fin);
    fread(hd.size, 1, 4, fin);

    int size = GetSize(hd.size, 7);
    int cur = 0;

    while(cur < size){
        fread(fr_hd.id, 1, 4, fin);
        fread(fr_hd.size, 1, 4, fin);
        int fr_size = GetSize(fr_hd.size, 8);
        fread(fr_hd.flags, 1, 2, fin);

        if((fr_hd.id[0] == 'T')&&(fr_hd.id[1] != 'X')){
            char coding;
            fread(&coding, 1, 1, fin);
            for(i = 0; i < 4; i++){
                Info.text_frames[text_fr_ind].name[i] = fr_hd.id[i];
            }
            Info.text_frames[text_fr_ind].name[4] = '\0';
            Info.text_frames[text_fr_ind].info = (char*)malloc(fr_size - 1);
            Info.text_frames[text_fr_ind].pos = ftell(fin);
            fread(Info.text_frames[text_fr_ind].info, 1, fr_size - 1, fin);
            Info.text_frames[text_fr_ind].size = fr_size - 1;
            text_fr_ind++;
        }

        else if((fr_hd.id[0] == 'W')&&(fr_hd.id[1] != 'X')){
            for(i = 0; i < 4; i++){
                Info.url_frames[url_fr_ind].name[i] = fr_hd.id[i];
            }
            Info.url_frames[url_fr_ind].name[4] = '\0';
            Info.url_frames[url_fr_ind].info = (char*)malloc(fr_size);
            Info.url_frames[url_fr_ind].pos = ftell(fin);
            fread(Info.url_frames[url_fr_ind].info, 1, fr_size, fin);
            Info.url_frames[url_fr_ind].size = fr_size;
            url_fr_ind++;
        }

        else if(strcmp(fr_hd.id, "COMM") == 0){
            char coding;
            fread(&coding, 1, 1, fin);
            fread(Info.Comm.language, 1, 3, fin);
            for(i = 0; i < 4; i++){
                Info.Comm.name[i] = fr_hd.id[i];
            }
            Info.Comm.name[4] = '\0';
            Info.Comm.info = (char*)malloc(fr_size - 4);
            Info.Comm.pos = ftell(fin);
            fread(Info.Comm.info, 1, fr_size - 4, fin);
            Info.Comm.size = fr_size - 4;
        }
        else{
            char* other = (char*)malloc(fr_size);
            fread(other, 1, fr_size, fin);
        }
        cur += 10 + fr_size;
    }
    if(strcmp(command, "--show") == 0){
        show();
    }
    if(strcmp(command, "--get") == 0){
        if(ShowOne(prop_name) == 1){
            printf("No such field!\n");
            getchar();
        }
    }
    if(strcmp(command, "--set") == 0){
        int res = change(prop_name, prop_value);
        if(res == -1){
            printf("No such field!\n");
            getchar();
        }
        else if(res != 0){
            printf("Size limit exceeded. Max value size = %d\n", res);
            getchar();
        }
        else printf("Changed successful\n\n");
    }

    fclose(fin);
    return 0;
}

int MakeArguments(int argc, char* argv[], char* filename, char* command, char* prop_name, char* prop_value){
    int i, cur;
    if(argc < 3)
        return 1;
    char s[15] = "";
    char s1[6] = "";
    strncat(s, argv[1], 10);
    if(strcmp(s, "--filepath") != 0)
        return 1;
    for(i = 0; i < strlen(argv[1]) - 11; i++){
        filename[i] = argv[1][i + 11];
    }
    cur = 2;
    if(argv[2][0] != '-'){
        for(i = 2; argv[i][0] != '-'; i++){
            strcat(filename, " ");
            strcat(filename, argv[i]);
        }
        cur = i;
    }

    if(strcmp(argv[cur], "--show") == 0){
        strcpy(command, "--show");
        return 0;
    }
    strncat(s1, argv[cur], 5);
    if(strcmp(s1, "--get") == 0){
        strcpy(command, "--get");
        for(i = 0; i < strlen(argv[cur]) - 6; i++){
            prop_name[i] = argv[cur][i + 6];
        }
        return 0;
    }
    if(strcmp(s1, "--set") == 0){
        strcpy(command, "--set");
        for(i = 0; i < strlen(argv[cur]) - 6; i++){
            prop_name[i] = argv[cur][i + 6];
        }
        cur++;
        for(i = 0; i < strlen(argv[cur]) - 8; i++){
            prop_value[i] = argv[cur][i + 8];
        }
        if(argc > cur + 1) prop_value[strlen(argv[cur]) - 8] = ' ';
        for(i = cur + 1; i < argc; i++){
            strcat(prop_value, argv[i]);
            if(i < argc - 1) strcat(prop_value, " ");
        }
        return 0;
    }
    return 1;
}

int ShowOne(char* prop_name){
    int i, j;
    int b = 0;
    printf("\n");
    if((prop_name[0] == 'T')&&(prop_name[1] != 'X')){
        for(i = 0; i < text_fr_ind; i++){
            if(strcmp(prop_name, Info.text_frames[i].name) == 0){
                printf("%s data: ", Info.text_frames[i].name);
                for(j = 0; j < Info.text_frames[i].size; j++){
                    printf("%c", Info.text_frames[i].info[j]);
                    b = 1;
                }
                break;
            }
        }
    }
    else if((prop_name[0] == 'W')&&(prop_name[1] != 'X')){
        for(i = 0; i < url_fr_ind; i++){
            if(strcmp(prop_name, Info.url_frames[i].name) == 0){
                printf("%s data: ", Info.text_frames[i].name);
                for(j = 0; j < Info.url_frames[i].size; j++){
                    printf("%c", Info.url_frames[i].info[j]);
                    b = 1;
                }
                break;
            }
        }
    }
    else if(strcmp(prop_name, "COMM") == 0){
        b = 1;
        printf("COMM data: ");
        for(i = 0; i < Info.Comm.size; i++){
            printf("%c", Info.Comm.info[i]);
        }
    }
    else return 1;
    if(b == 0) return 1;
    printf("\n");
    return 0;
}

int change(char* prop_name, char* prop_value){
    int i, j;
    int b = 0;
    char emp = '\0';
    if(prop_name[0] == 'T'){
        for(i = 0; i < text_fr_ind; i++){
            if(strcmp(prop_name, Info.text_frames[i].name) == 0){
                if(strlen(prop_value) > Info.text_frames[i].size)
                    return Info.text_frames[i].size;
                fseek(fin, Info.text_frames[i].pos, SEEK_SET);
                fwrite(prop_value, 1, strlen(prop_value), fin);
                for(j = strlen(prop_value); j < Info.text_frames[i].size; j++)
                    fwrite(&emp, 1, 1, fin);
                b = 1;
                break;
            }
        }
    }
    else if(prop_name[0] == 'W'){
        for(i = 0; i < url_fr_ind; i++){
            if(strcmp(prop_name, Info.url_frames[i].name) == 0){
                if(strlen(prop_value) > Info.url_frames[i].size)
                    return Info.url_frames[i].size;
                fseek(fin, Info.url_frames[i].pos, SEEK_SET);
                fwrite(prop_value, 1, strlen(prop_value), fin);
                for(j = strlen(prop_value); j < Info.url_frames[i].size; j++)
                    fwrite(&emp, 1, 1, fin);
                b = 1;
                break;
            }
        }
    }
    else if(strcmp(prop_name, "COMM") == 0){
        if(strlen(prop_value) > Info.Comm.size)
            return Info.Comm.size;
        fseek(fin, Info.Comm.pos, SEEK_SET);
        fwrite(prop_value, 1, strlen(prop_value), fin);
        for(j = strlen(prop_value); j < Info.Comm.size; j++)
            fwrite(&emp, 1, 1, fin);
        b = 1;
    }
    else return -1;
    if(b == 0) return -1;
    return 0;
}

void show(){
    int i, j;
    printf("\n");
    for(i = 0; i < text_fr_ind; i++){
        printf("%s ", Info.text_frames[i].name);
        for(j = 0; j < Info.text_frames[i].size; j++)
            printf("%c", Info.text_frames[i].info[j]);
        printf("\n");
    }
    for(i = 0; i < url_fr_ind; i++){
        printf("%s ", Info.url_frames[i].name);
        for(j = 0; j < Info.url_frames[i].size; j++)
            printf("%c", Info.url_frames[i].info[j]);
        printf("\n");
    }
    printf("\n%s ", Info.Comm.name);
    for(i = 0; i < Info.Comm.size; i++){
        printf("%c", Info.Comm.info[i]);
    }
    printf("\n");
}

int GetSize(char* size, int bit){
    int res = 0;
    int k = 0;
    int i, j;
    for(i = 0; i < 4; i++){
        int byte = size[3 - i];
        for(j = 0; j < bit; j++){
            int d = (byte & 1);
            res += d * pow(2, k);
            k++;
            byte = byte >> 1;
        }
    }
    return res;
}
//
// Created by alexa on 8.12.2019.
//
