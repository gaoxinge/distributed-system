## python

```
application
    |
    |
    v
   orm
    |
    |
    v
  db api
    |
    |
    v
  driver <-> connection pool
    |
    |
    v
 database
```

- [PEP 249 -- Python Database API Specification v2.0](https://www.python.org/dev/peps/pep-0249/)
- [Python](https://wiki.postgresql.org/wiki/Python)

## go

```
application
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

## java

```
application
    |
    |
    v
   orm
    |
    |
    v
jdbc datasource <-> connection pool
    |
    |
    v
jdbc driver     <-> connection pool
    |
    |
    v
 database
```