# pthread

## linux

```
$ gcc -pthread -o main main.c
$ gcc -o main main.c -lpthread
```

## windows

```
$ gcc -o main main.c
$ gcc -pthread -o main main.c
$ gcc -mthreads -o main main.c
$ gcc -o main main.c -lpthread
```

## reference

- [Multithreading in C](https://www.geeksforgeeks.org/multithreading-c-2/)
- [Threading in C Language with Linux (using GCC Complier)](https://www.includehelp.com/articles/threading-in-c-programming-language-with-gcc-linux.aspx)
- [Difference between -pthread and -lpthread while compiling](https://stackoverflow.com/questions/23250863/difference-between-pthread-and-lpthread-while-compiling)