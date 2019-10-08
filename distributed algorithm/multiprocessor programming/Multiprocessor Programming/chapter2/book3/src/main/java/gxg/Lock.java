package gxg;

public interface Lock {
    void acquire(int i);
    void release(int i);
}
