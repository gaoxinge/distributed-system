## architecture

|                          | leader follower                      | writer logger                        |
|--------------------------|--------------------------------------|--------------------------------------|
| heartbeat                | registry / cluster                   | writer: registry / logger: writer    |
| leader eletion           | registry                             | registry                             |
| fencing                  | r + term + biggest logger + recovery | r + term + biggest logger + recovery |
| log replicatin           | w + term + continuous / discrete     | w + term + continuous / discrete     |
| membership configuration | raft                                 | raft                                 |

## paper

- [dgryski/awesome-consensus](https://github.com/dgryski/awesome-consensus)
- [heidihoward/distributed-consensus-reading-list](https://github.com/heidihoward/distributed-consensus-reading-list)
- [Distributed consensus revised](https://www.cl.cam.ac.uk/techreports/UCAM-CL-TR-935.pdf)

## article

- [分布式共识(Consensus)：Viewstamped Replication、Raft以及Paxos](http://blog.kongfy.com/2016/05/%e5%88%86%e5%b8%83%e5%bc%8f%e5%85%b1%e8%af%86consensus%ef%bc%9aviewstamped%e3%80%81raft%e5%8f%8apaxos/)
