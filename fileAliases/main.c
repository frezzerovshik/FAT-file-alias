//
//  main.c
//  fileAliases
//
//  Created by Артем Шарапов on 27.04.2020.
//  Copyright © 2020 Hooba-booba. All rights reserved.
//

#include <stdio.h>

int main(int argc, const char * argv[]) {
    FILE *ptr;
    if ((ptr = fopen("/Users/frez2zerovshik/Downloads/Шарапов А.С. 1741 ОС вторая лабораторная.docx", "rt")) == NULL) {
        return 1;
    }
    printf("Размер: %d\n" , sizeof(ptr));
    return 0;
}
