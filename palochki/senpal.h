#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include <iostream>
#include <cstdlib>
#include <fstream>
//#include <que.h>
#define PERM 0666
using namespace std;

class Sender{
// внутренняя структура для сообщений
   struct Mess{
   long long type;// тип сообщения
// само сообщение
    char buf[100];
// Дополнительные поля: 
    int len; // размер сообщения в байтах
// pid процесса, посылавшего сообщение
    int pid; 
   };
// сообщение
   Mess msg;
   int key; // ключ
// дескриптор очереди сообщений
   int mesid; 
// pid текущего процесса
   int pid;
   public:
// Конструктор для сервера
// Требуется имя файла и символ
      Sender(const char*, char);
// Конструктор для клиента. 
// Добавляется еще параметр для различия
      Sender(const char*, char, int);
// деструктор
    ~Sender();
// чтение с возвратом кода ошибки
// ms - тело сообщения, type - тип сообщения
      unsigned char read( void* ms, long long type);
// посылка с возвратом кода ошибки
// ms - тело сообщения, type - тип сообщения
// len - размер тела сообщения
      unsigned char send( void* ms, int len, long long type);
// удаление очереди сообщений
      void delQueue();
};
int sti(char*);
void its(int, char*);