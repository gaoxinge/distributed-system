## architecture

|                          | leader follower                      | writer logger                        |
|--------------------------|--------------------------------------|--------------------------------------|
| heartbeat                | registry / cluster                   | writer: registry / logger: writer    |
| leader eletion           | registry                             | registry                             |
| fencing                  | r + term + biggest logger + recovery | r + term + biggest logger + recovery |
| log replicatin           | w + term + continuous / discrete     | w + term + continuous / discrete     |
| membership configuration | raft                                 | raft                                 |
