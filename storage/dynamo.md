## introduction

- [Amazon's Dynamo](https://www.allthingsdistributed.com/2007/10/amazons_dynamo.html)
- [Dynamo: Amazon’s Highly Available Key-value Store](https://www.allthingsdistributed.com/files/amazon-dynamo-sosp2007.pdf)

## architecture

|problem|technique|
|-|-|
|partition|consistent hashing|
|replication|quorum|
|consistency|vector clock|
|membership|gossip
