package gxg;

import java.util.concurrent.atomic.AtomicIntegerArray;

public class Filter implements Lock {
    private int n;
    private AtomicIntegerArray level;
    private AtomicIntegerArray victim;

    public Filter(int n) {
        this.n = n;
        level = new AtomicIntegerArray(n);
        victim = new AtomicIntegerArray(n-1);
    }

    private boolean exist(int i, int j) {
        for (int k = 0; k < this.n; k++) {
            if (k == i)
                continue;
            if (level.get(k) >= j) {
                return true;
            }
        }
        return false;
    }

    @Override
    public void acquire(int i) {
        for (int j = 1; j < this.n; j++) {
            level.set(i, j);
            victim.set(j-1, i);
            while (exist(i, j) && victim.get(j-1) == i) {}
        }
    }

    @Override
    public void release(int i) {
        level.set(i, 0);
    }
}
