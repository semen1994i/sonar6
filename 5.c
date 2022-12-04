/**
 * 5.c - вывод содержимого файла, работает и с кириллицей
 *
 * Copyright (c) 2021, Yaskelaynen Simon <yaskelya@cs.petrsu,ru>
 *
 * This code is licensed under a MIT-style license
 */
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>

int main(int argc, char **argv)
{
    setlocale(LC_ALL, "");
    /* Проверяем количество аргументов */
    if(argc != 2){
	fprintf(stderr, "Enter the 2 arguments\n");
	exit(EXIT_FAILURE);
    }

    /* Открываем файл */
    FILE *file;
    if(NULL == (file = fopen(argv[1], "r"))){
	perror(argv[1]);
	exit(EXIT_FAILURE);
    }

    /* Копируем содержимое */
    int c;
    while(WEOF != (c = fgetwc(file))){
	putwc(c, stdout);
	if(c != '\n')
	    putwc(' ', stdout);
    }

    /* Проверяем, почему вышли из цикла */
    if(ferror(file)){
	fprintf(stderr, "Read error\n");
	exit(EXIT_FAILURE);
    }

    /* Закрываем файл */
    if(EOF == fclose(file)){
	perror(argv[1]);
	exit(EXIT_FAILURE);
    }
    return 0;
}
