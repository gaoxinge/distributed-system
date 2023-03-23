## architecture

### 组织

|      | 语言有llvm | 语言没有llvm，且不使用llvm | 语言没有llvm，且使用llvm |
|------|------------|----------------------------|--------------------------|
| pull | 解释型     | 解释型                     | 解释型                   |
| push | 编译型90%  | 编译型80%                  | 编译型100%               |

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

### 向量化

- table
- batch
- stream

## paper

- [Volcano-An Extensible and Parallel Query Evaluation System](https://paperhub.s3.amazonaws.com/dace52a42c07f7f8348b08dc2b186061.pdf)
- [Query Evaluation Techniques for Large Databases](http://infolab.stanford.edu/~hyunjung/cs346/graefe.pdf)
- [Efficiently Compiling Efficient Query Plans for Modern Hardware](https://www.vldb.org/pvldb/vol4/p539-neumann.pdf)
- [How to Architect a Query Compiler](https://15721.courses.cs.cmu.edu/spring2018/papers/03-compilation/shaikhha-sigmod2016.pdf)
- [How to Architect a Query Compiler, Revisited](https://www.cs.purdue.edu/homes/rompf/papers/tahboub-sigmod18.pdf)

## article

- [数据库查询引擎的进化之路](https://zhuanlan.zhihu.com/p/41562506)
- [SQL 优化之火山模型](https://zhuanlan.zhihu.com/p/219516250)
- [查询编译综述](https://zhuanlan.zhihu.com/p/60965109)
- [Query Engines: Push vs. Pull](https://justinjaffray.com/query-engines-push-vs.-pull/)
- [Move to push-based execution model](https://github.com/duckdb/duckdb/issues/1583)
- [ClickHouse和他的朋友们（4）Pipeline处理器和调度器](https://bohutang.me/2020/06/11/clickhouse-and-friends-processor/)
