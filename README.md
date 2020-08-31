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
- [the morning paper](https://blog.acolyer.org/)
- [The Paper Trail](https://www.the-paper-trail.org/)
- [An introduction to distributed systems](https://github.com/aphyr/distsys-class)
- [awesome-distributed-systems](https://github.com/theanalyst/awesome-distributed-systems)
- [分布式系统(Distributed System)资料](https://github.com/ty4z2008/Qix/blob/master/ds.md)

## architecture

- basic
  - thread vs process
  - shared memory vs message passing
  - sync vs async
  - tcp vs http
- shared
  - shared nothing
  - shared disk
  - shared memory
  - shared everything
- state
  - stateless
  - stateful

## storage

- 块存储
- KV存储
- 对象存储
- 文件存储
- 数据库
- 搜索引擎
- 日志

### 文件存储

- 本地文件存储（DAS）
- 网络文件存储（FAS）
  - 存储区域网络（SAN）
  - 网络接入存储（SAN）

### 关系

- 数据库 ---> 文件存储 ---> 对象存储 ---> KV存储 ---> 块存储

## database

- [申砾：细说分布式数据库的过去、现在与未来](https://zhuanlan.zhihu.com/p/26676711)
- [数据中台之结构化大数据存储设计](https://yq.aliyun.com/articles/715254)
- [NoSQL Distilled](https://book.douban.com/subject/7952514/)

### relational database

- [basic](./database/relational%20database/basic)
- [mysql](./database/relational%20database//mysql)
- [postgres](./database/relational%20database//postgres)
- oracle

### cache database

- [basic](./database/cache%20database/basic)
- [redis](./database/cache%20database/redis)
- [memcached](./database/cache%20database/memcached)

### NoSQL

- key-value database
  - [basic](https://github.com/gaoxinge/distributed-system/tree/master/NoSQL/key-value%20database/basic)
  - [riak](https://github.com/gaoxinge/distributed-system/tree/master/NoSQL/key-value%20database/riak)
  - [voldemort](https://github.com/gaoxinge/distributed-system/tree/master/NoSQL/key-value%20database/voldemort)
  - dynamo
- embedded key-value database
  - [dbm](https://github.com/gaoxinge/distributed-system/tree/master/NoSQL/embedded%20key-value%20database/dbm)
  - [pickledb](https://github.com/gaoxinge/distributed-system/tree/master/NoSQL/embedded%20key-value%20database/pickledb)
  - [lmdb](https://github.com/gaoxinge/distributed-system/tree/master/NoSQL/embedded%20key-value%20database/lmdb)
  - [leveldb](https://github.com/gaoxinge/distributed-system/tree/master/NoSQL/embedded%20key-value%20database/leveldb)
  - [hyperleveldb](https://github.com/gaoxinge/distributed-system/tree/master/NoSQL/embedded%20key-value%20database/hyperleveldb)
  - [rocksdb](https://github.com/gaoxinge/distributed-system/tree/master/NoSQL/embedded%20key-value%20database/rocksdb)
  - [boltdb](https://github.com/gaoxinge/distributed-system/tree/master/NoSQL/embedded%20key-value%20database/boltdb)
- document-oriented database
  - [basic](https://github.com/gaoxinge/distributed-system/tree/master/NoSQL/document-oriented%20database/basic)
  - [mongodb](https://github.com/gaoxinge/distributed-system/tree/master/NoSQL/document-oriented%20database/mongodb)
  - [couchdb](https://github.com/gaoxinge/distributed-system/tree/master/NoSQL/document-oriented%20database/couchdb)
  - [orientdb](https://github.com/gaoxinge/distributed-system/tree/master/NoSQL/document-oriented%20database/orientdb)
  - [tinydb](https://github.com/gaoxinge/distributed-system/tree/master/NoSQL/document-oriented%20database/tinydb)
- column-family database
  - [cassandra](https://github.com/gaoxinge/distributed-system/tree/master/NoSQL/column-family%20database/cassandra)
  - [hbase](https://github.com/gaoxinge/distributed-system/tree/master/NoSQL/column-family%20database/hbase)