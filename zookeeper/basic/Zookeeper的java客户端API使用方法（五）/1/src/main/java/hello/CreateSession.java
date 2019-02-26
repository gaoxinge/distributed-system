package hello;

import org.apache.zookeeper.WatchedEvent;
import org.apache.zookeeper.Watcher;
import org.apache.zookeeper.ZooKeeper;

import java.io.IOException;

public class CreateSession implements Watcher {

    private void doSomething() {
        System.out.println("do something");
    }

    @Override
    public void process(WatchedEvent event) {
        System.out.println("Received watched event: " + event);
        if (event.getState() == Event.KeeperState.SyncConnected) {
            System.out.println("ZooKeeper session established");
            doSomething();
        }
    }

    public static void main(String[] args) throws IOException, InterruptedException {
        ZooKeeper zookeeper = new ZooKeeper("127.0.0.1:2181", 5000, new CreateSession());
        System.out.println(zookeeper.getState());
        Thread.sleep(Integer.MAX_VALUE);
    }
}
