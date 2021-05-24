/* *****************************************************************************
 *  Name:              Ada Lovelace
 *  Coursera User ID:  123456
 *  Last modified:     October 16, 1842
 **************************************************************************** */

import edu.princeton.cs.algs4.Queue;
import edu.princeton.cs.algs4.StdOut;

public class SortMerge1 {
    static Comparable[] aux;

    static void merge(Comparable[] a, int lo, int mid, int hi) {
        int i = lo;
        int j = mid + 1;
        for (int k = lo; k <= hi; ++k) {
            aux[k] = a[k];
        }
        for (int k = lo; k <= hi; ++k) {
            if (i > mid) a[k] = aux[j++];
            else if (j > hi) a[k] = aux[i++];
            else if (SortUtil.less(aux[j], aux[i])) a[k] = aux[j++];
            else a[k] = aux[i++];
        }
    }

    static Queue mergeQueue(Queue<Comparable> queue1, Queue<Comparable> queue2) {
        Queue<Comparable> r_queue = new Queue<Comparable>();

        while (!queue1.isEmpty() && !queue2.isEmpty()) {
            if (SortUtil.less(queue1.peek(), queue2.peek())) {
                r_queue.enqueue(queue1.dequeue());
            }
            else {
                r_queue.enqueue(queue2.dequeue());
            }
        }
        while (!queue1.isEmpty()) {
            r_queue.enqueue(queue1.dequeue());
        }
        while (!queue2.isEmpty()) {
            r_queue.enqueue(queue2.dequeue());
        }

        return r_queue;
    }

    static void sort(Comparable[] a, int lo, int hi) {
        if (lo >= hi) return;
        int mid = lo + (hi - lo) / 2;
        sort(a, lo, mid);
        sort(a, mid + 1, hi);
        merge(a, lo, mid, hi);
    }

    public static void main(String[] args) {
        Comparable[] a = { 1, 11, 2, 23, 3, 44, 5, 9, 6, 76, 4 };
        aux = new Comparable[a.length];
        sort(a, 0, a.length - 1);
        //SortUtil.show(a);

        Queue<Comparable> queue1 = new Queue<>();
        queue1.enqueue(1);
        queue1.enqueue(6);
        queue1.enqueue(7);
        queue1.enqueue(9);
        queue1.enqueue(12);
        queue1.enqueue(15);

        Queue<Comparable> queue2 = new Queue<>();
        queue2.enqueue(2);
        queue2.enqueue(12);
        queue2.enqueue(22);
        queue2.enqueue(32);
        queue2.enqueue(41);
        queue2.enqueue(55);

        Queue<Comparable> r = mergeQueue(queue1, queue2);
        while (!r.isEmpty()) {
            Comparable v = r.dequeue();
            StdOut.print(v + " ");
        }
    }
}
