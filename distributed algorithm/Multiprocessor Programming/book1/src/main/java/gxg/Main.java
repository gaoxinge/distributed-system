package gxg;

public class Main {
    public static void main(String[] args) throws Exception {
        Counter counter = new Counter(0);

        Thread t1 = new Thread(() -> {
            for (int i = 0; i < 5000; i++) {
                counter.inc();
            }
        });
        Thread t2 = new Thread(() -> {
            for (int i = 0; i < 5000; i++) {
                counter.inc();
            }
        });

        t1.setName("0");
        t2.setName("1");
        t1.start();
        t2.start();
        t1.join();
        t2.join();

        System.out.println(counter.get());

        Counter2 counter2 = new Counter2(0);

        Thread t3 = new Thread(() -> {
            for (int i = 0; i < 5000; i++) {
                counter2.inc();
            }
        });
        Thread t4 = new Thread(() -> {
            for (int i = 0; i < 5000; i++) {
                counter2.inc();
            }
        });

        t3.setName("0");
        t4.setName("1");
        t3.start();
        t4.start();
        t3.join();
        t4.join();

        System.out.println(counter2.get());
    }
}
