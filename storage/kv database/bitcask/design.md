# bitcask

## 假设

- key的个数小于一个常数
- value的大小等于一个常数

## 特性

- 根据记录个数（可配置），生成old data file
- key和value放在一个文件里面
- merge file放在一个文件里面
- key的类型是string，value的类型是[]byte
- 垃圾回收采用引用计数

## 数据结构

```
                       |---> Table
                       |
main ---> Bitcask ---> |
                       |
                       |---> FileManager
```

### `Value`


### `Table`

`map[string]Value`

- `Read`
- `Write`
- `Delete`
- `In`
- `Keys`
- `Len`
- `Range`

## 流程

### start

### read

1. 通过Table从内存里读取key对应的memoryValue
2. 通过FileManager从磁盘上读取memoryValue对应的diskValue

### write

1. 通过FileManager写入(key, diskValue)，并得到memoryValue
2. 通过Table写入(key, memoryValue)
3. 如果FileManager的active data file记录条数大于阈值，那么把现在的active data file置为old data file，并生成新的active data file

### delete

1. 通过FileManager写入(key, diskValue)，并得到memoryValue
2. 通过Table删除(key, memoryValue)
3. 如果FileManager的active data file记录条数大于阈值，那么把现在的active data file置为old data file，并生成新的active data file

### in

### keys

### len

### range

### merge

1. 定时调度触发合并
2. 通过FileManager，取得merge file对应的hint file和old data files，并合并得到旧table
3. 通过FileManager，生成旧table对应的merge file
4. 通过FileManager，删除旧table
5. 通过FileManager，生成merge file对应的hint file
6. 通过FileManager，生成hint file对应的新table
7. 根据新table，更新Table
8. 删除新table

## 垃圾回收

比较了一些垃圾回收实现的方式：

- 引用计数
  - 侵入性强，解耦难
  - concurrent reference counting
- 可达性分析
  - 粒度粗
  - stop the world

最终选择了可达性分析。

1. 通过定时调度或者合并触发
2. 获取Table和FileManager中的有引用的文件路径
3. 通过GC删除没有引用的文件路径

## 并发控制

- read：gc.read.lock ---> 内存读 ---> 磁盘读 ---> gc.read.unlock
- write：gc.read.lock ---> append.lock ---> 磁盘写 ---> key.lock ---> append.unlock ---> 内存写 ---> key.unlock ---> gc.read.lock
- delete：gc.read.lock ---> 如果没有key，报错 ---> 如果有 ---> append.lock ---> 磁盘写 ---> key.lock ---> append.unlock ---> 内存删 ---> key.unlock ---> gc.read.unlock
- in：gc.read.lock ---> 内存in ---> gc.read.unlock
- keys：gc.read.lock ---> 内存keys ---> gc.read.unlock
- len：gc.read.lock ---> 内存len ---> gc.read.unlock
- range: gc.read.lock ---> 内存range ---> gc.read.unlock
- merge：gc.read.lock ---> 合并的2，3，4，5，6 ---> 4和5，6可以并发 ---> gc.read.unlock
- gc：gc.write.lock ---> 垃圾回收 ---> gc.write.unlock

## 格式

### table

```
+-----+       +----------+---------+----------+---------+
| key | --->  | filePath | version | valuePos | valueSz |
+-----+       +----------+---------+----------+---------+
```

### data file

```
+--------+-------+---------+-----+-------+
| verion | keySz | valueSz | key | value |
+--------+-------+---------+-----+-------+
```

### merge file

```
+--------+-------+---------+-----+-------+
| verion | keySz | valueSz | key | value |
+--------+-------+---------+-----+-------+
```

### hint file

```
+---------+-------+----------+---------+-----+
| version | keySz | valuePos | valueSz | key |
+---------+-------+----------+---------+-----+
```
