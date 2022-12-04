/**
 * 1.c - копирование файла без буферизации
 *
 * Copyright (c) 2021, Yaskelaynen Simon <yaskelya@cs.petrsu,ru>
 *
 * This code is licensed under a MIT-style license
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char **argv)
{
    /* Проверяем, введены ли имена файлов */
    if(argc != 3){
	fprintf(stderr, "Программа принимает 2 дополнительных аргумента\n");
	exit(EXIT_FAILURE);
    }

    /* Размер буфера */
    size_t BUF_SIZE = 1024;

    /* Открываем файлы, проверяя на корректное открытие */
    FILE *in, *out;
    if(NULL == (in = fopen(argv[1], "r"))){
	perror(argv[1]);
	exit(EXIT_FAILURE);
    }
    if(NULL == (out = fopen(argv[2], "w"))){
	perror(argv[2]);
	exit(EXIT_FAILURE);
    }

    /* Копируем файл */
    char buf[BUF_SIZE];
    if(0 != setvbuf(in, NULL, _IONBF, BUF_SIZE)){
	fprintf(stderr, "Ошибка при отключении буферизации\n");
	exit(EXIT_FAILURE);
    }
    
    if(0 != setvbuf(out, NULL, _IONBF, BUF_SIZE)){
	fprintf(stderr, "Ошибка при отключении буферизации\n");
	exit(EXIT_FAILURE);
    }    
    size_t n;  
    while((n = fread(buf, 1, BUF_SIZE, in))){
	if(n != fwrite(buf, 1, n, out)){
	    fprintf(stderr, "Enter error");
	    exit(EXIT_FAILURE);
	}
    }

    /* Проверяем причину выхода из цикла */
    if(ferror(in)){
	fprintf(stderr, "Read error\n");
	exit(EXIT_FAILURE);
    }
    
    /* Закрываем файлы */
    if(EOF == (fclose(in))){
	perror(argv[1]);
	exit(EXIT_FAILURE);
    }

    if(EOF == (fclose(out))){
	perror(argv[1]);
	exit(EXIT_FAILURE);
    }
    return 0;
}
