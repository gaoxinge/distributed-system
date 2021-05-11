## architecture

|consistency|局部性|clock|conflict|concensus|服务端保证客户端|
|-|-|-|-|-|-|
|linearizability|Y|total order|no conflict/no concurrency|Y|Y|
|sequential consistency||total order||||
|causal consistency||partial order||||
|pram consistency||||||
|eventual consistency||||||

## wiki

- [Consistency model](https://en.wikipedia.org/wiki/Consistency_model)
- [Consistency Models](https://jepsen.io/consistency)

## paper

- [Consistency models in modern distributed systems. An approach to Eventual Consistency.](https://riunet.upv.es/bitstream/handle/10251/54786/TFMLeticiaPascual.pdf)
- [Consistency Part 2](http://www.cs.iit.edu/~iraicu/teaching/CS550-S11/lecture16.pdf)
- [Lec 12: Consistency Models – Sequential, Causal, and Eventual Consistency](https://www.cs.columbia.edu/~du/ds/assets/lectures/lecture12.pdf)
- [Consistency and Replication](https://www.cs.ucr.edu/~nael/cs202/lectures/lec15.pdf)
- [Consistency and Replication](http://csis.pace.edu/~marchese/CS865/Lectures/Chap7/Chapter7fin.htm)
- [10 consistency](http://www.cs.cmu.edu/~srini/15-446/S09/lectures/10-consistency.pdf)
- [CONSISTENCY](http://www.cs.cornell.edu/courses/cs5414/2017fa/notes/week12.pdf)
- [Consistency, causal and eventual](https://sergeiturukin.com/2017/06/29/eventual-consistency.html)
- [Transactions and consistency 101](https://sergeiturukin.com/2017/06/14/transactions-consistency.html)
- [Strong consistency models](https://aphyr.com/posts/313-strong-consistency-models)
- [Principles of Eventual Consistency](https://www.microsoft.com/en-us/research/publication/principles-of-eventual-consistency/)
- [Consistency in Non-Transactional Distributed Storage Systems](https://arxiv.org/abs/1512.00168)

## article

- [Eventual vs Strong Consistency in Distributed Databases](https://hackernoon.com/eventual-vs-strong-consistency-in-distributed-databases-282fdad37cf7)
- [分布式系统：一致性模型](https://zhuanlan.zhihu.com/p/59119088)
- [大神带我来搬砖](https://zhuanlan.zhihu.com/notFound)
  - [深入浅析分布式系统的一致性模型](https://zhuanlan.zhihu.com/p/66991710)
  - [深入浅析一致性模型之Sequential Consistency](https://zhuanlan.zhihu.com/p/67739048)
  - [深入浅析一致性模型之Linearizability](https://zhuanlan.zhihu.com/p/68736604)
  - [深入浅析一致性模型之Causal Consistency](https://zhuanlan.zhihu.com/p/71913226)
