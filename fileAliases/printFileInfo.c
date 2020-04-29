//
//  printFileInfo.c
//  fileAliases
//
//  Created by Артем Шарапов on 28.04.2020.
//  Copyright © 2020 Hooba-booba. All rights reserved.
//

#include "print.h"
#include <stdio.h>

#define GET_LEFT_BYTE 0xFFFF0000
#define GET_RIGHT_BYTE 0x0000FFFF
#define GET_DAY 0x1F0000
#define GET_MOUNTH 0x1E00000
#define GET_YEAR 0xFE000000
#define GET_SECS 0x1F
#define GET_MINS 0x7E0
#define GET_HOURS 0xF800
#define MINIMAL_YEAR_ALLOWED 1980
//Двубайтовый формат даты:
//биты 0–4 — день месяца, допускаются значения 1–31;
//биты 5–8 — месяц года, допускаются значения 1–12;
//биты 9–15 — год, считая от 1980 года («эпоха MS-DOS»), возможны значения от 0 до 127 включительно, то есть 1980–2107 годы.

//Двубайтовый формат времени:
//биты 0–4 — счётчик секунд (по две), допустимы значения 0–29, то есть 0–58 секунд;
//биты 5–10 — минуты, допустимы значения 0–59;
//биты 11–15 — часы, допустимы значения 0–23.

typedef struct Date {
    int day : 5;
    int mounth : 4;
    int year : 7;
} Date;

typedef struct Time {
    int seconds : 5;
    int minutes : 6;
    int hours : 5;
} Time;

void printFileInfo(FileSystem* system, int fileId) {
    int leftByte, rightByte;
    Date date;
    Time time;
    leftByte = rightByte = 0;
    for (int i = 0; i < system->superblock.rootSize / sizeof(File); ++i) {
        if (system->root[i].numberOfFirstFileBlock == fileId) {
            //Извлечение даты и времени
            leftByte = system->root[i].dateTime & GET_LEFT_BYTE;
            rightByte = system->root[i].dateTime & GET_RIGHT_BYTE;
            date.day = (leftByte & GET_DAY) >> 16;
            date.mounth = (leftByte & GET_MOUNTH) >> 21;
            date.year = (leftByte & GET_YEAR) >> 28;
            time.seconds = rightByte & GET_SECS;
            time.minutes = (rightByte & GET_MINS) >> 5;
            time.hours = (rightByte & GET_HOURS) >> 11;
            
            if ((date.day < 1 || date.day > 31) || (date.mounth < 1 || date.mounth > 12) || (date.year < 0 || date.year > 127) ||
                (time.seconds < 0 || time.seconds > 29) || (time.minutes < 0 || time.minutes > 59) || (time.hours < 0 || time.hours > 23)) {
                printf("Ошибка - некорректно указана дата создания\n");
                return;
            }
            
            printf("Название файла: %s\nДата создания: %d.%d.%d\nВремя создания: %d:%d:d\nНомер первого блока: %d\nАтрибуты: %d\nРазмер: %u\n",
                   system->root[i].nameOfFile, date.day, date.mounth, MINIMAL_YEAR_ALLOWED + date.year, time.hours, time.minutes, time.seconds * 2, fileId,system->root[i].attributes, system->root[i].size);
            return;
        }
    }
    printf("Файл с указаным ID не найден\n");
}
