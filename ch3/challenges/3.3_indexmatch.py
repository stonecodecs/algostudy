# returns index of largest value
def _hasMatchingIndex(a, start, end):
    N = (end - start)
    mid = start + (end - start) // 2
    if N <= 1: return mid == a[mid]
    if a[mid] < mid: # go right
        return _hasMatchingIndex(a, mid+1, end)
    elif a[mid] > mid: # go left
        return _hasMatchingIndex(a, start, mid)
    else: return mid == a[mid]

# returns both max and its index
def hasMatchingIndex(a):
    N = len(a)
    if N < 1: return None
    matchBool = _hasMatchingIndex(a, 0, N)
    return matchBool

res = hasMatchingIndex([-1,0,1,3,5,6,7,8,9])

print(f"Matching index? {res}")
