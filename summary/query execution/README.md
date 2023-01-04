## architecture

### DAG调度

- 单线程
- 线程池
- 无限线程

### 组织

|      | 语言有llvm | 语言没有llvm，且不使用llvm | 语言没有llvm，且使用llvm |
|------|------------|----------------------------|--------------------------|
| pull | 解释型     | 解释型                     | 解释型                   |
| push | 编译型90%  | 编译型80%                  | 编译型100%               |
| partial push: DAG pipline |
| partial push: DAG 线程池  |

### 向量化

- table
- batch
- stream

## article

- [数据库查询引擎的进化之路](https://zhuanlan.zhihu.com/p/41562506)
- [SQL 优化之火山模型](https://zhuanlan.zhihu.com/p/219516250)
- [查询编译综述](https://zhuanlan.zhihu.com/p/60965109)
- [Query Engines: Push vs. Pull](https://justinjaffray.com/query-engines-push-vs.-pull/)
- [Move to push-based execution model](https://github.com/duckdb/duckdb/issues/1583)
- [ClickHouse和他的朋友们（4）Pipeline处理器和调度器](https://bohutang.me/2020/06/11/clickhouse-and-friends-processor/)
