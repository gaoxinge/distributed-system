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
- [Distributed systems theory for the distributed systems engineer](https://www.the-paper-trail.org/post/2014-08-09-distributed-systems-theory-for-the-distributed-systems-engineer/)
- [Readings in distributed systems](http://christophermeiklejohn.com/distributed/systems/2013/07/12/readings-in-distributed-systems.html)
- [分布式系统前沿技术](https://www.infoq.cn/theme/48)

## tutorial

- [Distributed Algorithms](https://users.ics.aalto.fi/suomela/da/da-screen.pdf)
- [Principles of Distributed Computing ](https://disco.ethz.ch/courses/podc_allstars/)
- [DISTRIBUTED ALGORITHMS](http://read.pudn.com/downloads95/ebook/386159/Distributed.Algorithms.pdf)
- [分布式系统原理](https://wenku.baidu.com/view/d51da61414791711cc791714)
- [CSE5306: Distributed Systems](http://ranger.uta.edu/~jrao/CSE5306/fall2020/)
- [Distributed Computing: Principles, Algorithms, and Systems](https://www.cs.uic.edu/~ajayk/DCS-Book)
- [CS5620: Distributed Systems and Algorithms](http://homepage.divms.uiowa.edu/~ghosh/16618.html)
- [W4995-1: Distributed Systems](https://www.cs.columbia.edu/~du/ds/)
- [G22.3033-001: Distributed Systems](http://news.cs.nyu.edu/~jinyang/fa10/)
- [15-440: Distributed Systems](http://www.cs.cmu.edu/~dga/15-440/F10/)
- [COS-418: Distributed Systems](https://www.cs.princeton.edu/courses/archive/fall16/cos418/index.html)
- [COS-418: Distributed Systems](https://www.cs.princeton.edu/courses/archive/fall18/cos418/index.html)

## reference

- [arxiv](https://arxiv.org/)
- [系统](https://zhuanlan.zhihu.com/p/30264473)
- [数据库](https://www.jianshu.com/p/65570efd0ca3)
- [LESLIE LAMPORT'S HOME PAGE](http://www.lamport.org/)
- [Martin Kleppmann](https://martin.kleppmann.com/)
- [The Paper Trail](https://www.the-paper-trail.org/)
- [the morning paper](https://blog.acolyer.org/)
- [Metadata](http://muratbuffalo.blogspot.com/)
- [Read, Write, Execute](http://hh360.user.srcf.net/blog/)
- [Marc's Blog](https://brooker.co.za/blog/)
- [Peter Bailis :: Highly Available, Seldom Consistent](http://www.bailis.org/blog/)
- [db ranking](https://db-engines.com/en/ranking)
- [阿里中间件](http://140.205.61.252/)
- [美团技术](https://tech.meituan.com/)
- [数据库内核月报](http://mysql.taobao.org/monthly/)
- [阿里云服务产品目录](https://yunjisuanfuwu.com/aliyun)
- [NoSQL Distilled](https://book.douban.com/subject/7952514/)
- [数据中台之结构化大数据存储设计](https://yq.aliyun.com/articles/715254)
- [百万节点数据库扩展之道](https://www.jianshu.com/p/4427aebf9164)

## conference

### sosp

- [2021](https://sosp2021.mpi-sws.org/program.html)

## summary

### impossibility

- [flp](./summary/impossibility/flp)
- [cap](./summary/impossibility/cap)

### formal verification

- [coq](./summary/formal%20verification/coq)
- [tla](./summary/formal%20verification/tla)

### [clock](./summary/clock)

- [lamport clock](./summary/clock/lamport%20clock)
- [vector clock](./summary/clock/vector%20clock)
- [matrix clock](./summary/clock/matrix%20clock)
- [dotted version vectors](./summary/clock/dotted%20version%20vectors)
- [interval tree clock](./summary/clock/interval%20tree%20clock)
- concensus clock

### [gossip](./summary/gossip)

### [conflict](./summary/conflict)

- [git](./summary/conflict/git)
- [ot](./summary/conflict/ot)
- [mpds](./summary/conflict/mpds)
- [mrdt](./summary/conflict/mrdt)
- [crdt](./summary/conflict/crdt)

### quorum

### concensus

#### [CFT](./summary/concensus/CFT)

- [viewstamped replication](./summary/concensus/CFT/viewstamped%20replication)
- [paxos](./summary/concensus/CFT/paxos)
- [raft](./summary/concensus/CFT/raft)
- [zab](./summary/concensus/CFT/zab)
- [chubby](./summary/concensus/CFT/chubby)
- kafka
- [bookeeper](./summary/concensus/CFT/bookeeper)
- [pacifica](./summary/concensus/CFT/pacifica)

#### BFT

#### [BFT (probability)](./summary/concensus/BFT%20(probability))

- [bitcoin](./summary/concensus/BFT%20(probability)/bitcoin)
- [hotstuff](./summary/concensus/BFT%20(probability)/hotstuff)

### [replication](./summary/replication)

### [consistency](./summary/consistency)

- [linearizability](./summary/consistency/linearizability)
- [sequential consistency](./summary/consistency/sequential%20consistency)
- [causal consistency](./summary/consistency/causal%20consistency)
- [pram consistency](./summary/consistency/pram%20consistency)

### shared memory

- [shared memory](./summary/shared%20memory)

### transaction

- [scheduler](./summary/transaction/scheduler)
- [crash recovery](./summary/transaction/crash%20recovery)

### [storage](./summary/storage)

### [database](./summary/database)

### [snapshot](./summary/snapshot)

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

### 数据库

- [distributed file system](./storage/distributed-file-system.md)
- [gfs](./storage/gfs.md)
- [hdfs](./storage/hdfs.md)
- [curve](./storage/curve.md)
- [ceph](./storage/ceph.md)
- [cache](./storage/cache)
- [redis](./storage/redis)
- [memcached](./storage/memcached.md)
- [kv cluster](./storage/kv-cluster.md)
- [dynamo](./storage/dynamo.md)
- [voldemort](./storage/voldemort.md)
- [riak](./storage/riak.md)
- [gobeansdb](./storage/gobeansdb.md)
- [boltdb](./storage/boltdb.md)
- [leveldb](./storage/leveldb.md)
- [rocksdb](./storage/rocksdb.md)
- [agatedb](./storage/agatedb.md)
- [terarkdb](./storage/terarkdb.md)
- [pebble](./storage/pebble.md)
- [bitcask](./storage/bitcask.md)
- [sqlite](./storage/sqlite.md)
- oracle
- [mysql](./storage/mysql.md)
- [myrocks](./storage/myrocks.md)
- [postgres](./storage/postgres.md)
- [gluesql](./storage/gluesql.md)
- [peloton](./storage/peloton.md)
- [noisepage](./storage/noisepage.md)
- [duckdb](./storage/duckdb.md)
- [velox](./storage/velox.md)
- [chiselstore](./storage/chiselstore.md)
- [rqlite](./storage/rqlite.md)
- [toydb](./storage/toydb.md)
- [vitess](./storage/vitess.md)
- tdsql
- [kunlun](./storage/kunlun.md)
- aurora
- [cockroachdb](./storage/cockroachdb.md)
- [yugabytedb](./storage/yugabytedb.md)
- [baikaldb](./storage/baikaldb.md)
- [polardb](./storage/polardb.md)
- [oceanbase](./storage/oceanbase.md)
- [matrixorigin](./storage/matrixorigin.md)

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
