package hello;

import org.apache.zookeeper.*;

import java.io.IOException;

public class CreateNodeASync implements Watcher {

    private static ZooKeeper zookeeper;

    static class IStringCallback implements AsyncCallback.StringCallback {
        @Override
        public void processResult(int rc, String path, Object ctx, String name) {
            System.out.println("rc: " + rc);
            System.out.println("path: " + path);
            System.out.println("ctx: " + ctx);
            System.out.println("name: " + name);
        }
    }

    private void doSomething() {
        zookeeper.create(
                "/node_1",
                "123".getBytes(),
                ZooDefs.Ids.OPEN_ACL_UNSAFE,
                CreateMode.PERSISTENT,
                new IStringCallback(),
                "this is content"
        );
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
        zookeeper = new ZooKeeper("127.0.0.1:2181", 5000, new CreateNodeASync());
        System.out.println(zookeeper.getState());
        Thread.sleep(Integer.MAX_VALUE);
    }
}
