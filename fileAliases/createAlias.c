//
//  createAlias.c
//  fileAliases
//
//  Created by Артем Шарапов on 30.04.2020.
//  Copyright © 2020 Hooba-booba. All rights reserved.
//

#include "createAlias.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define SUBDIRECTORY 0x2

void createAlias(FileSystem* system, int fileID) {
    unsigned default_root_size = system->superblock.rootSize;
    int index_of_file = 0;
    char alias[13];
    alias[0] = '\0';
    File* buffer_root = (File*)malloc(default_root_size * sizeof(File));
    //Буфферизация исходного корневого каталога
    for (int i =0; i < default_root_size; ++i) {
        buffer_root[i] = system->root[i];
        if((buffer_root[i].attributes & SUBDIRECTORY) != SUBDIRECTORY) {
            if (buffer_root[i].numberOfFirstFileBlock == fileID) {
                index_of_file = i;
                printf("Вы собираетесь создать синоним файлу %s\nПожалуйста,введите синоним (не более 12 символов)\n" , buffer_root[i].nameOfFile);
                getchar();
                fgets(alias, 13, stdin);
            }
        }
    }
    if (alias[0] == '\0') {
        printf("Произошла ошибка, при создании синонима не обнаружен исходный файл\n");
        return;
    }
    File new_note = buffer_root[index_of_file];
    strcpy(new_note.nameOfFile, alias);
    free(system->root);
    system->root = (File*)malloc((default_root_size+1)*sizeof(File));
    for (int i = 0; i < default_root_size; ++i)
        system->root[i] = buffer_root[i];
    system->root[default_root_size] = new_note;
    system->superblock.rootSize++;
    free(buffer_root);
}
