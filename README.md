# distributed-system

## introduction

- [Starting Points in Distributed Systems, Pt. I: Background](https://augescens.com/2014/01/18/dist-systems-starting-pts-i/)
- [Distributed computing](https://en.wikipedia.org/wiki/Distributed_computing)
- [A Thorough Introduction to Distributed Systems](https://hackernoon.com/a-thorough-introduction-to-distributed-systems-3b91562c9b3c)
- [Distributed systems for fun and profit](http://book.mixu.net/distsys/single-page.html)
- [Fallacies of distributed computing](https://en.wikipedia.org/wiki/Fallacies_of_distributed_computing)
- [Notes on Distributed Systems for Young Bloods](https://wenku.baidu.com/view/2ed750eeaf1ffc4fff47ac70.html)
- [An introduction to distributed systems](https://github.com/aphyr/distsys-class)
- [awesome-distributed-systems](https://github.com/theanalyst/awesome-distributed-systems)
- [分布式系统(Distributed System)资料](https://github.com/ty4z2008/Qix/blob/master/ds.md)
- [The System Design Primer](https://github.com/donnemartin/system-design-primer)
- [Designing Data-Intensive Applications](https://book.douban.com/subject/26197294/)
- [设计数据密集型应用](https://github.com/Vonng/ddia)
- [分布式系统前沿技术](https://www.infoq.cn/theme/48)

## algorithm

- [Distributed Algorithms](https://users.ics.aalto.fi/suomela/da/da-screen.pdf)
- [Principles of Distributed Computing ](https://disco.ethz.ch/courses/podc_allstars/)
- [DISTRIBUTED ALGORITHMS](http://read.pudn.com/downloads95/ebook/386159/Distributed.Algorithms.pdf)
- [分布式系统原理](https://wenku.baidu.com/view/d51da61414791711cc791714)
- [CSE5306: Distributed Systems](http://ranger.uta.edu/~jrao/CSE5306/fall2020/)
- [Distributed Computing: Principles, Algorithms, and Systems](https://www.cs.uic.edu/~ajayk/DCS-Book)
- [CS5620: Distributed Systems and Algorithms](http://homepage.divms.uiowa.edu/~ghosh/16618.html)

## reference

- [arxiv](https://arxiv.org/)
- [系统](https://zhuanlan.zhihu.com/p/30264473)
- [数据库](https://www.jianshu.com/p/65570efd0ca3)
- [LESLIE LAMPORT'S HOME PAGE](http://www.lamport.org/)
- [Martin Kleppmann](https://martin.kleppmann.com/)
- [the morning paper](https://blog.acolyer.org/)
- [The Paper Trail](https://www.the-paper-trail.org/)

### sosp

- [2021](https://sosp2021.mpi-sws.org/program.html)

## summary

### clock

- [clock](./summary/clock)
- [lamport clock](./summary/lamport%20clock)
- [vector clock](./summary/vector%20clock)
- [matrix clock](./summary/matrix%20clock)
- [dotted version vectors](./summary/dotted%20version%20vectors)
- [interval tree clock](./summary/interval%20tree%20clock)

### snapshot

- [snapshot](./summary/snapshot)

### gossip

- [gossip](./summary/gossip)

### conflict

- [conflict](./summary/conflict)
- [git](./summary/git)
- [ot](./summary/ot)
- [mpds](./summary/mpds)
- [mrdt](./summary/mrdt)
- [crdt](./summary/crdt)

### concensus

- [viewstamped replication](./summary/viewstamped%20replication)
- [paxos](./summary/paxos)
- [raft](./summary/raft)
- [zab](./summary/zab)
- kafka
- [bookeeper](./summary/bookeeper)
- [pacifica](./summary/pacifica)
- [summary](./summary/concensus_summary)

### consistency

- [consistency](./summary/consistency)
- [linearizability](./summary/linearizability)
- [sequential consistency](./summary/sequential%20consistency)
- [causal consistency](./summary/causal%20consistency)
- [pram consistency](./summary/pram%20consistency)

### shared memory

- [shared memory](./summary/shared%20memory)

### impossibility

- [flp](./summary/flp)
- [cap](./summary/cap)

### formal verification

- [coq](./summary/coq)
- [tla](./summary/tla)

## architecture

- shared
  - shared nothing
  - shared disk
  - shared memory
  - shared everything
- message
  - 1
    - udp/tcp
    - queue/channel
    - message broker
  - 2
    - block/nonblock
    - sync/async
- log
  - application log
  - database
    - log structured kv database
    - wal log
    - replication log
  - log-based message broker
  - consensus/atomic broadcast
  - cdc/etl
- state
  - stateless
  - stateful
- stream
  - immutable
  - mutable
- process
  - batch
  - stream

## 存储

### 分类

- 数据库
- KV存储/对象存储
- 文件存储/块存储
- 日志

### 存算分离

- 计算的一致性
- 存储的一致性

### 架构

```
+--------------+
| sql          |
+--------------+
| data process |
+--------------+
| nosql        |
+--------------+
| log          |
+--------------+
```

### 常用网站

- [db ranking](https://db-engines.com/en/ranking)
- [阿里云服务产品目录](https://yunjisuanfuwu.com/aliyun)

### 参考文献

- [NoSQL Distilled](https://book.douban.com/subject/7952514/)
- [数据中台之结构化大数据存储设计](https://yq.aliyun.com/articles/715254)

### cache database

- [basic](./storage/cache%20database/basic)
- [redis](./storage/cache%20database/redis)
- [memcached](./storage/cache%20database/memcached)

### kv database

- [basic](./storage/kv%20database/basic)
- [boltdb](./storage/kv%20database/boltdb)
- [leveldb](./storage/kv%20database/leveldb)
- [rocksdb](./storage/kv%20database/rocksdb)
- [pebble](./storage/kv%20database/pebble)
- [bitcask](./storage/kv%20database/bitcask)

### kv database cluster

- [dynamo](./storage/kv%20database%20cluster/dynamo)
- [voldemort](./storage/kv%20database%20cluster/voldemort)
- [riak](./storage/kv%20database%20cluster/riak)
- [gobeansdb](./storage/kv%20database%20cluster/gobeansdb)
- [matrixorigin](./storage/kv%20database%20cluster/matrixorigin)

### relational database

- [basic](./storage/relational%20database/basic)
- [sqlite](./storage/relational%20database/sqlite)
- oracle
- [mysql](./storage/relational%20database/mysql)
- [myrocks](./storage/relational%20database/myrocks)
- [postgres](./storage/relational%20database/postgres)

### relational database cluster

- [kunlun](./storage/relational%20database%20cluster/kunlun)
- [baikaldb](./storage/relational%20database%20cluster/baikaldb)
- [polardb](./storage/relational%20database%20cluster/polardb)
- [oceanbase](./storage/relational%20database%20cluster/oceanbase)
- [cockroachdb](./storage/relational%20database%20cluster/cockroachdb)
- [yugabytedb](./storage/relational%20database%20cluster/yugabytedb)

### file system

- [basic](./storage/file%20system/basic)
- [gfs](./storage/file%20system/gfs)
- [hdfs](./storage/file%20system/hdfs)
- [curve](./storage/file%20system/curve)
- [ceph](./storage/file%20system/ceph)

### document database

- [basic](./storage/document%20database/basic)
- [mongodb](./storage/document%20database/mongodb)
- [rethinkdb](./storage/document%20database/rethinkdb)
- [couchdb](./storage/document%20database/couchdb)
- couchbase/membase

### column database

- [hbase](./storage/column%20database/hbase)
- [cassandra](./storage/column%20database/cassandra)

### other

- [mr](./storage/other/mr)
- [pig](./storage/other/pig)
- [hive](./storage/other/hive)
- [dremel](./storage/other/dremel)
- [bigquery](./storage/other/bigquery)
- [drill](./storage/other/drill)
- [kylin](./storage/other/kylin)
- [impala](./storage/other/impala)
- [presto](./storage/other/presto)
- [snowflake](./storage/other/snowflake)
- [datafuse](./storage/other/datafuse)
- [matrixorigin](./storage/other/matrixorigin)
- [clickhouse](./storage/other/clickhouse)
- [hologres](./storage/other/hologres)
- [greenplum](./storage/other/greenplum)
- [starrocks](./storage/other/starrocks)
- [doris](./storage/other/doris)
- [kudu](./storage/other/kudu)

## message broker

### design

- exact once message passing
  - atomic commit
  - idempotent
- message order
- fault tolerance
  - drop message
  - apply backpressure
  - buffer message
    - ring buffer

### comparison

|                            | tcp                           | message broker |
|----------------------------|-------------------------------|----------------|
| exact once message passing | sequence number               | log-based      |
| message order              | sequence number               | log-based      |
| falut tolerance            | slide window, traffic control | log-based      |

## data process

### design

- expressive: sql
- expressive: fork-join, dag
- expressive: language, framework
- throughoutput: partition, parallel
- fault tolerance

### comparison

|          | spark / flink          | tensorflow / pytorch      | pregel |
|----------|------------------------|---------------------------|--------|
| parallel | dag + cluster parallel | dag + standalone parallel |        |

## the future of data systems

- data integration
  - distributed transaction vs log-based system
  - kappa architecture vs lambda architecture vs lambda plus architecture
    - [kappa-architecture.com](http://milinda.pathirage.org/kappa-architecture.com/)
    - [Lambda Architecture](http://lambda-architecture.net/)
    - [From Lambda to Kappa: A Guide on Real-time Big Data Architectures](https://www.talend.com/blog/2017/08/28/lambda-kappa-real-time-big-data-architectures/)
  - batch process vs stream process
- aiming for correctness
  - the end-to-end argument
    - inner vs outer
  - correctness and fault-tolerance
  - timeliness and integrity
