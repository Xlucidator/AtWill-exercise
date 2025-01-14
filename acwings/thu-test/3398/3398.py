
# calculate x = \sqrt[m]{A}
def mth_root(A, m):
    if A < 0:
        if m % 2 == 0:
            raise ValueError
        return - mth_root(-A, m)
    if A == 0:
        return 0
    
    ## now we could assume A > 0 : f(x) = x^m - A = 0
    # Newton Iteration Method:  x_{k+1} = x_k - \frac{x_k - n/x_k^{m-1}}{m}
    x_k = 1 << (A.bit_length() // m + 1) # x_0 is greater than the mth_root of A
    # m_minor_1 = m - 1
    while True:
        res_check = pow(x_k, m) # python would optimized itself
        if (res_check == A): return x_k
        x_k = x_k - (x_k - A * x_k // res_check) // m # python would optimized itself

n, m = map(int, input().split())
print(mth_root(n, m))