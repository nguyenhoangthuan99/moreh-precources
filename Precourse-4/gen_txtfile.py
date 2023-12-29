import random
from tqdm import tqdm
s = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghjklmnopqrstuvwxyz0123456789!@#$%^&*()_+"
s = list(s)
n = len(s)

for i in range(11,26):
    print(i)
    with open(f"file/{2**i//1024}k.txt","w") as fp:
        n = 2**i//1024
        for j in tqdm(range(n)):
            fp.write("".join(random.choices(s, k=1023))+"\n")