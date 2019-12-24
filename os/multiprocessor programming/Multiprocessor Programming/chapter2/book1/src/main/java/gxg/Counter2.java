package gxg;

public class Counter2 {
    private int value;

    public Counter2(int c) {
        value = c;
    }

    public void inc() {
        value++;
    }

    public int get() {
        return value;
    }
}
