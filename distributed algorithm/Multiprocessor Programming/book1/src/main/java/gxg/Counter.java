package gxg;

public class Counter {
    private int value;
    private Lock lock;

    public Counter(int c) {
        value = c;
        lock = new Peterson();
    }

    public void inc() {
        String name = Thread.currentThread().getName();
        int i = name.equals("0") ? 0 : 1;
        lock.acquire(i);
        value++;
        lock.release(i);
    }

    public int get() {
        return value;  // TODO: add lock
    }
}
