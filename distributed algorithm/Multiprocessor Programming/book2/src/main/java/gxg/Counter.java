package gxg;

public class Counter {
    private int value;
    private Lock lock;

    public Counter(int c) {
        value = c;
        lock = new Filter(5);
    }

    public void inc() {
        String name = Thread.currentThread().getName();
        int i;
        switch (name) {
            case "0":
                i = 0;
                break;
            case "1":
                i = 1;
                break;
            case "2":
                i = 2;
                break;
            case "3":
                i = 3;
                break;
            case "4":
                i = 4;
                break;
            default:
                i = -1;
        }

        lock.acquire(i);
        value++;
        lock.release(i);
    }

    public int get() {
        return value;  // TODO: add lock
    }
}