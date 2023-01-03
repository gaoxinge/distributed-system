## architecture

### DAG调度

- 单线程
- 线程池
- 无限线程

### 组织

|      | 语言有llvm | 语言没有llvm，且不使用llvm | 语言没有llvm，且使用llvm |
|------|------------|----------------------------|--------------------------|
| push | 解释型     | 解释型                     | 解释型                   |
| pull | 编译型90%  | 编译型80%                  | 编译型100%               |

### 向量化

- table
- batch
- stream

## article

- [Query Engines: Push vs. Pull](https://justinjaffray.com/query-engines-push-vs.-pull/)
