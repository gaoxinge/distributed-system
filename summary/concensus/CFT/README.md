## architecture

|                | register                   | multi paxos        | generalized paxos          |
|----------------|----------------------------|--------------------|----------------------------|
| implementation | classic paxos / fast paxos | multi paxos / raft | generalized paxos / epaxos |

- use registry to implement distributed logging

|                          | leader + follower                                    | writer + reader + logger                        |
|--------------------------|------------------------------------------------------|-------------------------------------------------|
| heartbeat                | registry / cluster                                   | 1. writer: registry / cluster 2. logger: writer |
| leader eletion           | registry + term                                      | registry + term                                 |
| fencing                  | r quorum + term + longest logger + recovery          | r quorum + term + longest logger + recovery     |
| log replication          | 1. w quorum + term + ack / commit 2. w quorum + term | w quorum + term                                 |
| read                     | 1. leader read 2. r quorum read                      | r quorum read                                   |
| membership configuration | registry + quorum intersection                       | registry + quorum intersection                  |

## paper

- [Can’t we all just agree?](https://blog.acolyer.org/2015/03/01/cant-we-all-just-agree/)
- [dgryski/awesome-consensus](https://github.com/dgryski/awesome-consensus)
- [heidihoward/distributed-consensus-reading-list](https://github.com/heidihoward/distributed-consensus-reading-list)
- [Distributed consensus revised](https://www.cl.cam.ac.uk/techreports/UCAM-CL-TR-935.pdf)

## article

- [分布式共识(Consensus)：Viewstamped Replication、Raft以及Paxos](http://blog.kongfy.com/2016/05/%e5%88%86%e5%b8%83%e5%bc%8f%e5%85%b1%e8%af%86consensus%ef%bc%9aviewstamped%e3%80%81raft%e5%8f%8apaxos/)
