/* *****************************************************************************
 *  Name:              Ada Lovelace
 *  Coursera User ID:  123456
 *  Last modified:     October 16, 1842
 **************************************************************************** */

public class SortQuick {

    static int partition(Comparable[] a, int lo, int hi) {
        Comparable k = a[lo];
        int i = lo;
        int j = hi;
        while (i < j) {
            while (i <= j && a[i].compareTo(k) <= 0) ++i;
            while (i <= j && SortUtil.less(k, a[j])) --j;
            if (i < j) {
                SortUtil.exch(a, i, j);
            }
        }
        if (SortUtil.less(a[j], a[lo])) {
            SortUtil.exch(a, lo, j);
        }

        return j;
    }

    static void sort(Comparable[] a, int lo, int hi) {
        if (lo >= hi) return;
        int mid = partition(a, lo, hi);
        sort(a, lo, mid - 1);
        sort(a, mid + 1, hi);
    }

    public static void main(String[] args) {
        Comparable[] a = { 1, 11, 2, 23, 3, 44, 5, 9, 6, 76, 4 };
        sort(a, 0, a.length - 1);
        SortUtil.show(a);
    }
}
