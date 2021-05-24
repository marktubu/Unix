/* *****************************************************************************
 *  Name:              Ada Lovelace
 *  Coursera User ID:  123456
 *  Last modified:     October 16, 1842
 **************************************************************************** */

public class SortInsertion {

    static void sort(Comparable[] a) {
        int N = a.length;
        for (int i = 1; i < N; ++i) {
            for (int j = i; j > 0 && SortUtil.less(a[j], a[j - 1]); --j) {
                SortUtil.exch(a, j, j - 1);
            }
        }
    }

    public static void main(String[] args) {
        Comparable[] a = { 1, 11, 2, 23, 3, 44, 5, 9, 6, 76, 4 };
        sort(a);
        SortUtil.show(a);
    }
}
