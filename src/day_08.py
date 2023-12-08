navs = input().strip()
nav_len = len(navs)
input()
neighs = dict()
while True:
    try:
        line = input().strip()
        node = line.split(" = ")[0]
        left = line.split(" = ")[1].split(", ")[0][1:]
        right = line.split(" = ")[1].split(", ")[1][:-1]
        neighs[node] = (left, right)
    except EOFError:
        break

i = 0
cur_node = "AAA"
while cur_node != "ZZZ":
    if navs[i % nav_len] == "L":
        cur_node = neighs[cur_node][0]
    else:
        cur_node = neighs[cur_node][1]
    i += 1
print(i)


def next_node(v, i):
    return neighs[v][0] if navs[i % nav_len] == "L" else neighs[v][1]


def get_cycle_length(v):
    i = 0
    dists_z = []
    dists = dict()
    dists[(v, i)] = 0
    while (next_node(v, i % nav_len), (i + 1) % nav_len) not in dists:
        v = next_node(v, i)
        i += 1
        dists[(v, i % nav_len)] = i
        # I could return direcly in this if condition, but this is the code I used to verify that
        # the Z-ending vertex repeats exactly after as many steps as is the distance between v and
        # that vertex, and there is exactly one such vertex.
        if v[-1] == "Z":
            dists_z.append(i)
    return dists_z[0]


ans2 = 1


def gcd(a, b):
    if a == 0:
        return b
    return gcd(b % a, a)


def lcm(a, b):
    return (a * b) // gcd(a, b)


for node in neighs:
    if node[-1] == "A":
        ans2 = lcm(ans2, get_cycle_length(node))
print(ans2)
