## architecture

### 实现 

- pull
  - volcano
- push
  - callback
  - consumer-producer / DAG
    - single thread
    - multi thread
      - thread pool
      - no thread pool

### 编译 vs 解释

|      | 语言有llvm | 语言没有llvm，且不使用llvm | 语言没有llvm，且使用llvm |
|------|------------|----------------------------|--------------------------|
| pull | 解释型     | 解释型                     | 解释型                   |
| push | 编译型90%  | 编译型80%                  | 编译型100%               |

### 向量化

- table
- batch
- stream

### 分布式

#### 阶段

- logical plan
- standalone physical plan
- distributed physical plan
  - DAG: stage / pipeline
    - source
    - transform 
    - sink
  - operator: writer + reader / sender + receiver
    - merge
    - shuffle / redistribution / repartition
    - broadcast

#### 流程

- 角色
  - master
  - worker
  - client
- 流程
  - worker register master
  - client send sql to master
  - master parse sql to distributed physical plan
  - master send distributed physical plan to worker
  - master send begin flag to source
  - worker execute and data flow between distributed physical plan
  - sink send end flag to master
  - master send data to client

## paper

- [Volcano-An Extensible and Parallel Query Evaluation System](https://paperhub.s3.amazonaws.com/dace52a42c07f7f8348b08dc2b186061.pdf)
- [Query Evaluation Techniques for Large Databases](http://infolab.stanford.edu/~hyunjung/cs346/graefe.pdf)
- [MonetDB/X100: Hyper-Pipelining Query Execution](https://www.cidrdb.org/cidr2005/papers/P19.pdf)
- [Rethinking SIMD Vectorization for In-Memory Databases](http://www.cs.columbia.edu/~orestis/sigmod15.pdf)
- [Efficiently Compiling Efficient Query Plans for Modern Hardware](https://www.vldb.org/pvldb/vol4/p539-neumann.pdf)
- [Everything You Always Wanted to Know About Compiled and Vectorized Queries But Were Afraid to Ask](https://www.vldb.org/pvldb/vol11/p2209-kersten.pdf)
- [Vectorization vs. Compilation in Query Execution](https://15721.courses.cs.cmu.edu/spring2016/papers/p5-sompolski.pdf)
- [How to Architect a Query Compiler](https://15721.courses.cs.cmu.edu/spring2018/papers/03-compilation/shaikhha-sigmod2016.pdf)
- [How to Architect a Query Compiler, Revisited](https://www.cs.purdue.edu/homes/rompf/papers/tahboub-sigmod18.pdf)
- [Morsel-Driven Parallelism: A NUMA-Aware Query Evaluation Framework for the Many-Core Age](https://15721.courses.cs.cmu.edu/spring2019/papers/14-scheduling/p743-leis.pdf)
- [Push vs. Pull-Based Loop Fusion in Query Engines](https://arxiv.org/pdf/1610.09166.pdf)
- [Relaxed Operator Fusion for In-Memory Databases: Making Compilation, Vectorization, and Prefetching Work Together At Last](http://www.vldb.org/pvldb/vol11/p1-menon.pdf)
- [Adaptive Execution of Compiled Queries](https://db.in.tum.de/~leis/papers/adaptiveexecution.pdf)
- [Multi-Core, Main-Memory Joins: Sort vs. Hash Revisited](http://www.vldb.org/pvldb/vol7/p85-balkesen.pdf)
- [Looking Ahead Makes Query Plans Robust](http://www.vldb.org/pvldb/vol10/p889-zhu.pdf)

## article

- [数据库查询引擎的进化之路](https://zhuanlan.zhihu.com/p/41562506)
- [SQL 优化之火山模型](https://zhuanlan.zhihu.com/p/219516250)
- [查询编译综述](https://zhuanlan.zhihu.com/p/60965109)
- [Query Engines: Push vs. Pull](https://justinjaffray.com/query-engines-push-vs.-pull/)
- [Move to push-based execution model](https://github.com/duckdb/duckdb/issues/1583)
- [ClickHouse和他的朋友们（4）Pipeline处理器和调度器](https://bohutang.me/2020/06/11/clickhouse-and-friends-processor/)
