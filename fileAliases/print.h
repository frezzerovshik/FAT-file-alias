//
//  print.h
//  fileAliases
//
//  Created by Артем Шарапов on 28.04.2020.
//  Copyright © 2020 Hooba-booba. All rights reserved.
//

#pragma once
#include "FileSystem.h"

#define EOC 0xFF
#define BROKEN 0x0FE

void printFAT(FileSystem* system);
void printSuperblockInfo (FileSystem* system);
void printRootInfo(FileSystem* system);
