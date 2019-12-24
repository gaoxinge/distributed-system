package gxg;

import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.atomic.AtomicIntegerArray;

public class Peterson implements Lock {
    private AtomicIntegerArray flag;
    private AtomicInteger victim;

    public Peterson() {
        flag = new AtomicIntegerArray(2);
        victim = new AtomicInteger();
    }

    @Override
    public void acquire(int i) {
        flag.set(i, 1);
        victim.set(i);
        while (flag.get(1 - i) == 1 && victim.get() == i) {}
    }

    @Override
    public void release(int i) {
        flag.set(i, 0);
    }
}
