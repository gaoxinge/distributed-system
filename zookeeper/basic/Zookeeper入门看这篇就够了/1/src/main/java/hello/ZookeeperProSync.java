package hello;

import org.apache.zookeeper.WatchedEvent;
import org.apache.zookeeper.Watcher;
import org.apache.zookeeper.ZooKeeper;
import org.apache.zookeeper.data.Stat;

import java.util.concurrent.CountDownLatch;

public class ZookeeperProSync implements Watcher {
    private static CountDownLatch connectedSemaphore = new CountDownLatch(1);
    private static ZooKeeper zk = null;
    private static Stat stat = new Stat();

    public void process(WatchedEvent event) {
        if (event.getState() == Event.KeeperState.SyncConnected) {
            if (event.getType() == Event.EventType.None && event.getPath() == null) {
                connectedSemaphore.countDown();
            } else if (event.getType() == Event.EventType.NodeDataChanged) {
                try {
                    System.out.println("配置已修改，新值为：" + new String(zk.getData(event.getPath(), true, stat)));
                } catch (Exception e) {

                }
            }
        }
    }

    public static void main(String[] args) throws Exception {
        String path = "/username";
        zk = new ZooKeeper("localhost:2181", 5000, new ZookeeperProSync());
        connectedSemaphore.await();
        System.out.println(new String(zk.getData(path, true, stat)));
        Thread.sleep(Integer.MAX_VALUE);
    }
}
