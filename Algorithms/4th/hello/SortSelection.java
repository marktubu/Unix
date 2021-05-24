/* *****************************************************************************
 *  Name:              Ada Lovelace
 *  Coursera User ID:  123456
 *  Last modified:     October 16, 1842
 **************************************************************************** */

public class SortSelection {

    static void sort(Comparable[] a) {
        int N = a.length;
        for (int i = 0; i < N; ++i) {
            int min = i;
            for (int j = i; j < N; ++j) {
                if (SortUtil.less(a[j], a[min])) {
                    min = j;
                }
            }
            SortUtil.exch(a, min, i);
        }
    }

    public static void main(String[] args) {
        Comparable[] a = { 1, 11, 2, 23, 3, 44, 5, 9, 6, 76, 4 };
        sort(a);
        SortUtil.show(a);
    }
}
