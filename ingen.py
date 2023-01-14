def f2(n, dreq):
    a = [
        [0] * n
        for i in range(n)
    ]
    def wall(hlo, hhi, wlo, whi):
        hlo, hhi = sorted([hlo, hhi])
        wlo, whi = sorted([wlo, whi])
        for r in range(hlo, hhi):
            for c in range(wlo, whi):
                a[r][c] = 1
    minlen = [n]
    while len(minlen) <= dreq:
        minlen.append((minlen[-1] - 5) // 2)

    def rec(r0, c0, h, hdrc, w, wdrc, d):
        def wl(hlo, hhi, wlo, whi):
            wall(
                r0 + hlo * hdrc,
                r0 + hhi * hdrc,
                c0 + wlo * wdrc,
                c0 + whi * wdrc,
            )
        if d == dreq:
            t0 = 0
            t1 = minlen[d] // 3
            t2 = minlen[d] * 2 // 3
            t3 = minlen[d] - 1

            wl(t0 + 1, t2 + 0, t0 + 1, t0 + 3)
            wl(t0 + 1, t0 + 3, t0 + 1, t2 + 0)

            wl(t2 + 1, t3 + 0, t0 + 1, t0 + 3)
            wl(t0 + 1, t0 + 3, t2 + 1, t3 + 0)

            wl(t2 + 1, t2 + 3, t0 + 1, t1 + 0)
            wl(t0 + 1, t1 + 0, t2 + 1, t2 + 3)

            wl(t2 - 2, t2 + 0, t0 + 4, t1 + 0)
            wl(t0 + 4, t1 + 0, t2 - 2, t2 + 0)

            wl(t1 + 1, t2 + 0, t0 + 4, t0 + 6)
            wl(t0 + 4, t0 + 6, t1 + 1, t2 + 0)
        else:
            nn = minlen[d + 1]
            wl(1, 3, 0, nn + 2)
            wl(1, 3, nn + 3, w)
            wl(nn + 3, nn + 4, 0, nn - 1)
            wl(nn + 3, nn + 4, nn + 6, w)
            wl(1, nn + 3, nn, nn + 2)
            wl(nn + 4, h, nn, nn + 2)
            wl(0, nn + 3, nn + 3, nn + 5)
            wl(nn + 4, h, nn + 3, nn + 5)
            rec(r0 + (nn + 3) * hdrc, c0 + (nn) * wdrc, nn, -hdrc, nn, -wdrc, d + 1)
            rec(r0 + (nn + 3) * hdrc, c0 + (nn + 5) * wdrc, nn, -hdrc, w - nn - 5, +wdrc, d + 1)
            rec(r0 + (nn + 4) * hdrc, c0 + (nn) * wdrc, h - nn - 4, +hdrc, nn, -wdrc, d + 1)
            rec(r0 + (nn + 4) * hdrc, c0 + (nn + 5) * wdrc, h - nn - 4, +hdrc, w - nn - 5, +wdrc, d + 1)

    rec(0, 0, n, 1, n, 1, 0)
    return a


def pa(a):
    for rw in a: print(*rw, sep='')

print(1000, 1000)
pa(f2(1000, 5))
