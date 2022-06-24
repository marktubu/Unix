class ListNode {
    val: number
    next: ListNode | null
    constructor(val?: number, next?: ListNode | null) {
        this.val = (val===undefined ? 0 : val)
        this.next = (next===undefined ? null : next)
    }
}

export function twoSum(numbers: number[], target: number): number[] {
    // write code here
    let dict = {}
    for(let i=0;i<numbers.length;i++){
        let num = numbers[i]
        if(dict[num] != null){
            return [dict[num], i+1]
        }
        let other = target - num
        dict[other] = i+1
    }

    return []
}