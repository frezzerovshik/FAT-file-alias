//
//  main.c
//  fileAliases
//
//  Created by Артем Шарапов on 27.04.2020.
//  Copyright © 2020 Hooba-booba. All rights reserved.
//

#include <stdio.h>
#include "FileSystem.h"
#include "readingFile.h"
#include "print.h"

//FAT image reading tool

int main(int argc, const char * argv[]) {
    FileSystem* system = readingFile("path");
    printSuperblockInfo(system);
    printRootInfo(system);
    return 0;
}
