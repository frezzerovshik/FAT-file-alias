//
//  printFileTree.c
//  fileAliases
//
//  Created by Артем Шарапов on 29.04.2020.
//  Copyright © 2020 Hooba-booba. All rights reserved.
//

#include "print.h"
#include <stdlib.h>
#include <stdio.h>
#define SUBDIRECTORY 0x2
#define _true 1

int haveSubdir (File dir, FileSystem* system, File* directories, int countDirectories) {
    int numberInFAT = 0;
    for (int i = 0 ; i < system->superblock.FATsize / 8; i++) {
          if (system->FAT[i][0] == dir.numberOfFirstFileBlock) {
            numberInFAT = i;
            break;
        }
    }
    int i = numberInFAT;
    while (system->FAT[i][1] != EOC) {
        for (int j = 0; j < countDirectories; ++j) {
            if (directories[j].numberOfFirstFileBlock == system->FAT[i][0]) {
                return 1;
            }
        }
        i++;
    }
    return 0;
}

void printCatalog(File dir, FileSystem* system, File* directories, File* files, int countFiles, int countDirectories) {
    int numberInFAT = 0;
    for (int i = 0 ; i < system->superblock.FATsize / 8; i++) {
        if (system->FAT[i][0] == dir.numberOfFirstFileBlock) {
            numberInFAT = i;
            break;
        }
    }
    for (int i = numberInFAT; i < system->superblock.FATsize / 8; ++i) {
        for (int j = 0; j < countFiles; ++j) {
            if (files[j].numberOfFirstFileBlock == system->FAT[i][0]) {
                printf("Файл: %s\n", files[j].nameOfFile);
            }
            if (system->FAT[i][1] == EOC) {
                return;
            }
        }
        for (int j = 0; j < countDirectories; ++j) {
            if (directories[j].numberOfFirstFileBlock == system->FAT[i][0]){
                printCatalog(directories[j], system, directories, files, countFiles, countDirectories);
            }
            if (system->FAT[i][1] == EOC) {
                return;
            }
        }
    }
}

void printFileTree(FileSystem* system) {
    File *files, *directories;
    int countFiles, countDirectories;
    files = directories = NULL;
    countFiles = countDirectories = 0;
    int iFiles, iDir;
    iFiles = iDir = 0;
    for (int i = 0; i < system->superblock.rootSize; ++i) {
        if (system->root[i].attributes == SUBDIRECTORY	)
            countDirectories++;
        else
            countFiles++;
    }
    files = (File*)malloc(countFiles * sizeof(File));
    directories = (File*)malloc(countDirectories * sizeof(File));
    for (int i = 0; i < system->superblock.rootSize; ++i) {
        if ((system->root[i].attributes & SUBDIRECTORY) == SUBDIRECTORY) {
            directories[iDir] = system->root[i];
            iDir++;
        }
        else {
            files[iFiles] = system->root[i];
            iFiles++;
        }
    }
    if (countDirectories == 0) {
        for (int i = 0; i < countFiles; ++i) {
            printf("Имя файла: %s Расположение Root\n" , files[i].nameOfFile);
        }
    }
    else {
        for (int i = 0; i < countDirectories ; ++i) {
            if (haveSubdir(directories[i], system, directories, countDirectories) != 0)
                printCatalog(directories[i], system, directories, files, countFiles, countDirectories);
        }
    }
    free(files);
    free(directories);
}
