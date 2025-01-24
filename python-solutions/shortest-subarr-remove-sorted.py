from bisect import bisect_left, bisect_right

# https://leetcode.com/problems/shortest-subarray-to-be-removed-to-make-array-sorted/solutions/6046262/beats-100-00-easy-and-step-by-step-breakdown/?envType=daily-question&envId=2024-11-15

# NOTE: I could have done far better than this
# just check along prefix and suffix

def find_length_of_shortest_subarray(arr) -> int:
    start_problem, end_problem = -1,-1
    prev = arr[0]

    for i, v in enumerate(arr):
        if prev > v:
            end_problem = i
            if start_problem == -1:
                start_problem = i
        prev = v
    
    if start_problem == -1:
        return 0
    
    result = len(arr)


    start_length, end_length = len(arr)-start_problem, end_problem
    result = min(start_length, end_length)

    i = 0
    while i <= min(start_length-1, len(arr)- end_length-1):
        a = bisect_left(arr, arr[start_problem-i-1], lo=end_problem)
        b = bisect_right(arr, arr[end_problem+i], hi=start_problem)
        result = min(
            result, 
            a-(start_problem-i), 
            end_problem+i-b,
        )
        i+=1

    return result



if __name__ == '__main__':
    test_cases = [
        ([1, 2, 3, 10, 4, 2, 3, 5], 3),
        ([1, 2, 3, 10, 3, 5], 1),
        ([1, 2, 3, 3, 3, 3, 3, 3, 10, 4, 2, 3, 5], 3),
        ([5, 4, 3, 2, 1], 4),
        ([1, 2, 3], 0),
        ([6,3,10,11,15,20,13,3,18,12], 8)
    ]
    for tc in test_cases:
        nums, expected = tc
        actual = find_length_of_shortest_subarray(nums)
        print(f"Test case: {nums} - Expected: {expected}, Actual: {actual} - {'Passed' if actual == expected else 'Failed'}")

'''
         s       e
1 2 3 30 5 12 15 4 6 9
0 1 2 3  4 5  6  7 8 9
'''