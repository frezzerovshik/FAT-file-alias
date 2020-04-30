//
//  main.c
//  fileAliases
//
//  Created by Артем Шарапов on 27.04.2020.
//  Copyright © 2020 Hooba-booba. All rights reserved.
//

#include <stdio.h>
#include "readingFile.h"
#include "print.h"
#include "createAlias.h"
#include "memoryDealloc.h"
#include <string.h>
#define DIR 0x2

#define _true 1
#define _false 0
int main(int argc, const char * argv[]) {
    char path[256];
    char func;
    printf("Введите путь до образа файловой системы, расположенном на локальном носителе\n");
    fgets(path, 256, stdin);
    char* editedPath = (char*)malloc(sizeof(char)*(strlen(path)-1));
    for (int i = 0; i < strlen(path)-1; ++i) {
        editedPath[i] = path[i];
    }
    FileSystem* system = readingFile(editedPath);
    printSuperblockInfo(system);
    printf("Сведения о содержании корневого каталога:\n");
    printRootInfo(system);

    int flag = _true;
    while (flag == _true) {
        printf("1 - вывести на экран таблицу размещения файлов (FAT)\n2 - вывести содержимое текстовых файлов на экран\n3 - вывести на экран информацию о конкретном файле/папке\n4 - вывести на экран полное файловое дерево\n5 - создать алиас(синоним файла) [без поддержки каталогов]\n6 - выход из программы\n");
        func = fgetc(stdin);
        switch (func) {
            case '1': {
                printFAT(system);
                getchar();
                break;
            }
            case '2': {
                int file_id = 0;
                for (int i = 0; i < system->superblock.rootSize; ++i) {
                    if (system->root[i].attributes != DIR)
                        printf("ID файла: %d Название файла: %s\n" ,i , system->root[i].nameOfFile);
                }
                printf("Пожалуйста, введите ID файла\n");
                scanf("%d" , &file_id);
                printTextFile(system, system->root[file_id].numberOfFirstFileBlock);
                getchar();
                break;
            }
            case '3': {
                int file_id = 0;
                for (int i = 0; i < system->superblock.rootSize; ++i) {
                        printf("ID файла: %d Название файла: %s\n" ,system->root[i].numberOfFirstFileBlock, system->root[i].nameOfFile);
                }
                printf("Пожалуйста, введите ID файла\n");
                scanf("%d" , &file_id);
                printFileInfo(system, file_id);
                getchar();
                break;
            }
            case '4': {
                printFileTree(system);
                getchar();
                break;
            }
            case '5': {
                int file_id = 0;
                for (int i = 0; i < system->superblock.rootSize; ++i) {
                    if ((system->root[i].attributes & DIR) != DIR)
                        printf("ID файла: %d Название файла: %s\n" ,system->root[i].numberOfFirstFileBlock, system->root[i].nameOfFile);
                }
                printf("Пожалуйста, введите ID файла\n");
                scanf("%d" , &file_id);
                createAlias(system, file_id);
                getchar();
                break;
            }
            case '6': {
                flag = _false;
                break;
            }
            default:
                break;
        }
    }
    memory_dealloc(system, fopen(path, "rb"));
    system = NULL;
    return 0;
}
