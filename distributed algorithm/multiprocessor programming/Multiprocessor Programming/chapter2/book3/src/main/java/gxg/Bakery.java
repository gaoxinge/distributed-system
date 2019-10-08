package gxg;

import java.util.concurrent.atomic.AtomicIntegerArray;

public class Bakery implements Lock {
    private int n;
    private AtomicIntegerArray flag;
    private AtomicIntegerArray label;

    public Bakery(int n) {
        this.n = n;
        flag = new AtomicIntegerArray(n);
        label = new AtomicIntegerArray(n);
    }

    private int max() {
        int m = label.get(0);
        for (int i = 1; i < n; i++) {
            int t = label.get(i);
            if (m < t)
                m = t;
        }
        return m;
    }

    private boolean exist(int i) {
        int l1 = label.get(i);
        for (int k = 0; k < n; k++) {
            if (k == i)
                continue;
            int f = flag.get(k);
            int l2 = label.get(k);
            if ((f != 0) && ((l1 > l2) || (l1 == l2 && i > k)))
                return true;
        }
        return false;
    }

    public void acquire(int i) {
        flag.set(i, 1);
        label.set(i, max() + 1);
        while (exist(i)) {}
    }

    public void release(int i) {
        flag.set(i, 0);
    }
}
