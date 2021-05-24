function rank(key, a) {
    var lo = 0;
    var hi = a.length - 1;
    while (lo <= hi) {
        var mid = Math.floor(lo + (hi - lo) / 2);
        if (key < a[mid])
            hi = mid - 1;
        else if (key > a[mid])
            lo = mid + 1;
        else
            return mid;
    }
    return -1;
}
var a = [1, 3, 5, 6, 7, 8, 9, 11, 12, 21, 33];
var k = 21;
var idx = rank(k, a);
console.log("idx", idx);
