package hello;

import org.apache.zookeeper.*;

import java.io.IOException;

public class CreateNodeSync implements Watcher {

    private static ZooKeeper zookeeper;

    private void doSomething() {
        try {
            String path = zookeeper.create("/node_2", "123".getBytes(), ZooDefs.Ids.OPEN_ACL_UNSAFE, CreateMode.PERSISTENT);
            System.out.println("return path: " + path);
        } catch (KeeperException | InterruptedException e) {
            e.printStackTrace();
        }
        System.out.println("do something");
    }

    @Override
    public void process(WatchedEvent event) {
        System.out.println("Received watched event: " + event);
        if (event.getState() == Event.KeeperState.SyncConnected) {
            doSomething();
        }
    }

    public static void main(String[] args) throws IOException, InterruptedException {
        zookeeper = new ZooKeeper("127.0.0.1:2181", 5000, new CreateNodeSync());
        System.out.println(zookeeper.getState());
        Thread.sleep(Integer.MAX_VALUE);
    }
}
