/**
 * 6.c - длина строки
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
	fprintf(stderr, "Программа принимает 2 аргумента!\n");
	exit(EXIT_FAILURE);
    }
    /* Открываем файл, в который запишем нашу строку */
    FILE *file;
    if(NULL == (file = fopen("file.txt", "w+"))){
	perror("file.txt");
	exit(EXIT_FAILURE);
    }

    /* Записываем строку */
    if(EOF == fputs(argv[1], file)){
	fprintf(stderr, "Ошибка при вычислении длины строки");
	exit(EXIT_FAILURE);
    }
    
    /* Закрываем файлы */
    if(EOF == (fclose(file))){
	perror("file/.txt");
	exit(EXIT_FAILURE);
    }

    /* Теперь открываем файл, чтобы считать нашу строку */
    if(NULL == (file = fopen("file.txt", "r"))){
	perror("file.txt");
	exit(EXIT_FAILURE);
    }

    /* Записываем строку */
    int c, n = 0;
    while((c = fgetwc(file)) != WEOF){
	n++;
    }

    /* Проверяем, почему вышли из цикла */
    if(ferror(file)){
	fprintf(stderr, "Ошибка при вычислении длины строки\n");
	exit(EXIT_FAILURE);
    }

    /* Выводим длину строки */
    printf("%d\n", n);

    /* Закрываем файлы */
    if(EOF == (fclose(file))){
	perror("file/.txt");
	exit(EXIT_FAILURE);
    }

    /* Удаляем файл */
    if(remove("file.txt") != 0){
	fprintf(stderr, "Ошибка удаления временного файла\n");
	exit(EXIT_FAILURE);
    }
    return 0;
}
