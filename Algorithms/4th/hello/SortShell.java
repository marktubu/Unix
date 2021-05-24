/* *****************************************************************************
 *  Name:              Ada Lovelace
 *  Coursera User ID:  123456
 *  Last modified:     October 16, 1842
 **************************************************************************** */

public class SortShell {

    static void sort(Comparable[] a) {
        int N = a.length;
        int h = 1;
        while (h < N / 3) h = h * 3 + 1;
        while (h >= 1) {
            for (int i = h; i < N; ++i) {
                for (int j = i; j >= h && SortUtil.less(a[j], a[j - h]); j -= h) {
                    SortUtil.exch(a, j, j - h);
                }
            }
            h = h / 3;
        }
    }

    public static void main(String[] args) {
        Comparable[] a = { 1, 11, 2, 23, 3, 44, 5, 9, 6, 76, 4 };
        sort(a);
        SortUtil.show(a);
    }
}
