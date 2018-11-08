## python

```
application <-> concurrency control
    |
    |
    v
   orm
    |
    |
    v
  db api    <-> connection pool
    |
    |
    v
  driver 
    |
    |
    v
 database
```

- [PEP 249 -- Python Database API Specification v2.0](https://www.python.org/dev/peps/pep-0249/)
- [Python](https://wiki.postgresql.org/wiki/Python)

## go

```
application  <-> concurrency control
    |
    |
    v
   orm
    |
    |
    v
database/sql <-> connection pool
    |
    |
    v
  driver
    |
    |
    v
 database
```

- [dive into golang database/sql(1)](https://www.jianshu.com/p/3b0b3a4c83da)
- [dive into golang database/sql(2)](https://www.jianshu.com/p/807257fcb985)
- [dive into golang database/sql(3)](https://www.jianshu.com/p/cd8cee3d7fc3)

## java

```
application         <-> concurrency control
    |
    |
    v
   orm
    |
    |
    v
jdbc datasource api <-> connection pool
    |
    |
    v
 jdbc api
    |
    |
	v
  driver
    |
    |
    v
 database
```

- [JDBC数据源(DataSource)的简单实现](http://blog.51cto.com/lavasoft/265073)