```
$ cd external
$ git clone git@github.com:fmtlib/fmt.git --depth=1
$ git clone git@github.com:hyrise/sql-parser.git --depth=1

$ cd ..
$ cmake -B build/ -G "Unix Makefiles"
$ cmake --build build/
$ build/main.exe
====================================
|a|       b|
|1|2.000000|
|9|9.000000|
|3|4.000000|
|2|4.000000|
|1|4.000000|
|3|5.000000|
|6|7.000000|
====================================
SelectStatement
        Fields:
                a
                b
        Sources:
                t
        Search Conditions:
                >
                        a
                        1
        OrderBy:
                a
                ascending
        Limit:
                3
        Offset:
                1
====================================
|a0|      a1|
| 3|5.000000|
| 3|4.000000|
| 6|7.000000|
====================================
```