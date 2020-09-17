# distributed-system

## introduction

- [Starting Points in Distributed Systems, Pt. I: Background](https://augescens.com/2014/01/18/dist-systems-starting-pts-i/)
- [Distributed computing](https://en.wikipedia.org/wiki/Distributed_computing)
- [A Thorough Introduction to Distributed Systems](https://hackernoon.com/a-thorough-introduction-to-distributed-systems-3b91562c9b3c)
- [Distributed systems for fun and profit](http://book.mixu.net/distsys/single-page.html)
- [Fallacies of distributed computing](https://en.wikipedia.org/wiki/Fallacies_of_distributed_computing)
- [Notes on Distributed Systems for Young Bloods](https://wenku.baidu.com/view/2ed750eeaf1ffc4fff47ac70.html)
- [system-design-primer](https://github.com/donnemartin/system-design-primer)
- [Designing Data-Intensive Applications](https://book.douban.com/subject/26197294/)
- [分布式系统前沿技术](https://www.infoq.cn/theme/48)

## algorithm

- [Distributed Algorithms](https://users.ics.aalto.fi/suomela/da/da-screen.pdf)
- [Principles of Distributed Computing ](https://disco.ethz.ch/courses/podc_allstars/)
- [DISTRIBUTED ALGORITHMS](http://read.pudn.com/downloads95/ebook/386159/Distributed.Algorithms.pdf)
- [CSE5306: Distributed Systems](http://ranger.uta.edu/~jrao/CSE5306/fall2019/)
- [W4995-1: Distributed Systems](https://www.cs.columbia.edu/~du/ds/)
- [CS5620: Distributed Systems and Algorithms](http://homepage.divms.uiowa.edu/~ghosh/16618.html)
- [Distributed Computing: Principles, Algorithms, and Systems](https://www.cs.uic.edu/~ajayk/DCS-Book)

## summary

### clock

- [clock](./summary/clock)
- [lamport clock](./summary/lamport%20clock)
- [matrix clock](./summary/matrix%20clock)
- [interval tree clock](./summary/interval%20tree%20clock)

### snapshot

- [snapshot](./summary/snapshot)

### consistency

- [consistency](./summary/consistency)
- [linearizability](./summary/linearizability)
- [sequential consistency](./summary/sequential%20consistency)

### conflict

- [conflict](./summary/conflict)
- [mpds](./summary/mpds)
- [git](./summary/git)
- [ot](./summary/ot)
- [mrdt](./summary/mrdt)
- [crdt](./summary/crdt)

### shared memory

- [shared memory](./summary/shared%20memory)

## reference

- [arxiv](https://arxiv.org/)
- [系统](https://zhuanlan.zhihu.com/p/30264473)
- [数据库](https://www.jianshu.com/p/65570efd0ca3)
- [the morning paper](https://blog.acolyer.org/)
- [The Paper Trail](https://www.the-paper-trail.org/)
- [An introduction to distributed systems](https://github.com/aphyr/distsys-class)
- [awesome-distributed-systems](https://github.com/theanalyst/awesome-distributed-systems)
- [分布式系统(Distributed System)资料](https://github.com/ty4z2008/Qix/blob/master/ds.md)

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

- 块存储
- KV存储
- 对象存储
- 文件存储
- 数据库

### 文件存储

- 本地文件存储（DAS）
- 网络文件存储（FAS）
  - 存储区域网络（SAN）
  - 网络接入存储（SAN）
  
### 数据库

- [NoSQL Distilled](https://book.douban.com/subject/7952514/)
- [数据中台之结构化大数据存储设计](https://yq.aliyun.com/articles/715254)

### embedding database

- [basic](./database/embedding%20database/basic)
- [boltdb](./database/embedding%20database/boltdb)

### cache database

- [basic](./database/cache%20database/basic)
- [redis](./database/cache%20database/redis)
- [memcached](./database/cache%20database/memcached)

### kv database

- [basic](./database/kv%20database/basic)
- [leveldb](./database/kv%20database/leveldb)
- [rocksdb](./database/kv%20database/rocksdb)

### kv database cluster

- dynamo
- [voldemort](./database/kv%20database%20cluster/voldemort)
- [riak](./database/kv%20database%20cluster/riak)
- [gobeansdb](./database/kv%20database%20cluster/gobeansdb)

### relational database

- [basic](./database/relational%20database/basic)
- oracle
- [mysql](./database/relational%20database//mysql)
- [postgres](./database/relational%20database/postgres)

### relational database cluster

- [cockroachdb](./database/relational%20database%20cluster/cockroachdb)

### document database

- [basic](./database/document%20database/basic)
- [mongodb](./database/document%20database/mongodb)
- [couchdb](./database/document%20database/couchdb)
- couchbase/membase

### column database

- [hbase](./database/column%20database/hbase)
- [cassandra](./database/column%20database/cassandra)

### sql no hadoop

- [pig](./database/sql%20on%20hadoop/pig)
- [hive](./database/sql%20on%20hadoop/hive)

### data warehouse

- [snowflake](./database/data%20warehouse/snowflake)
- [clickhouse](./database/data%20warehouse/clickhouse)
- [greenplum](./database/data%20warehouse/greenplum)

### 关系

- 数据库 ---> 文件存储 ---> 对象存储 ---> KV存储 ---> 块存储

### 存算分离

- 存储的一致性
- 计算的一致性

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

- expressive: language, framework, sql
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