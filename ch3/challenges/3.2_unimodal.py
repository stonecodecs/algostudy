# returns index of largest value
def _unimodalMax(a, start, end):
    N = (end - start)
    mid = start + (end - start) // 2
    if N == 1: return mid
    if mid + 1 < end and a[mid] < a[mid + 1]: # go right
        return _unimodalMax(a, mid+1, end)
    elif mid - 1 >= start and a[mid] < a[mid - 1]: # go left
        return _unimodalMax(a, start, mid)
    else: return mid

# returns both max and its index
def unimodalMax(a):
    N = len(a)
    if N < 1: return None, None
    max_i = _unimodalMax(a, 0, N)
    return a[max_i], max_i

maxval, maxidx = unimodalMax([-22,10,25,23])

print(f"{maxval}, {maxidx}")
