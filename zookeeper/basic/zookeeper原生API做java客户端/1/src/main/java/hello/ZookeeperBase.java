package hello;

import org.apache.zookeeper.*;

import java.util.concurrent.CountDownLatch;

public class ZookeeperBase {

    private static final String CONNECT_ADDR = "localhost:2181";
    private static final int SESSION_OUTTIME = 2000;
    private static final CountDownLatch connectedSemaphore = new CountDownLatch(1);

    public static void main(String[] args) throws Exception {
        ZooKeeper zk = new ZooKeeper(CONNECT_ADDR, SESSION_OUTTIME, (WatchedEvent event) -> {
            Watcher.Event.KeeperState keeperState = event.getState();
            Watcher.Event.EventType eventType = event.getType();
            if (Watcher.Event.KeeperState.SyncConnected == keeperState && Watcher.Event.EventType.None == eventType) {
                connectedSemaphore.countDown();
                System.out.println("zk建立连接");
            }
        });
        connectedSemaphore.await();

        zk.create("/testRoot", "testRoot".getBytes(), ZooDefs.Ids.OPEN_ACL_UNSAFE, CreateMode.PERSISTENT);  // 创建父节点
        zk.create("/testRoot/children", "children data".getBytes(), ZooDefs.Ids.OPEN_ACL_UNSAFE, CreateMode.PERSISTENT);  // 创建子节点

        zk.setData("/testRoot", "modify data root".getBytes(), -1);  // 修改节点数据
        System.out.println(new String(zk.getData("/testRoot", false, null))); // 获取节点数据
        System.out.println(zk.getChildren("/testRoot", false));  // 获取子节点名字
        System.out.println(zk.exists("/testRoot/children", false));  // 判断节点是否存在

        zk.delete("/testRoot/children", -1);  // 删除子节点
        zk.delete("/testRoot", -1);  // 删除父节点

        zk.close();
    }
}
