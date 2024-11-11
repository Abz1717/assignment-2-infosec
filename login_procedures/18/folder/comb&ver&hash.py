from itertools import product

# allowed characters within 'a' to 'k'
allowed_chars = "abcdefghijk"
# final filtered combinations meeting XOR condition and range restriction
filtered_combinations = [
    ('a', 'a', 'g'), ('a', 'b', 'd'), ('a', 'c', 'e'), ('a', 'd', 'b'), ('a', 'e', 'c'),
    ('a', 'g', 'a'), ('b', 'a', 'd'), ('b', 'b', 'g'), ('b', 'c', 'f'), ('b', 'd', 'a'),
    ('b', 'f', 'c'), ('b', 'g', 'b'), ('c', 'a', 'e'), ('c', 'b', 'f'), ('c', 'c', 'g'),
    ('c', 'e', 'a'), ('c', 'f', 'b'), ('c', 'g', 'c'), ('d', 'a', 'b'), ('d', 'b', 'a'),
    ('d', 'd', 'g'), ('d', 'e', 'f'), ('d', 'f', 'e'), ('d', 'g', 'd'), ('d', 'h', 'k'),
    ('d', 'i', 'j'), ('d', 'j', 'i'), ('d', 'k', 'h'), ('e', 'a', 'c'), ('e', 'c', 'a'),
    ('e', 'd', 'f'), ('e', 'e', 'g'), ('e', 'f', 'd'), ('e', 'g', 'e'), ('e', 'h', 'j'),
    ('e', 'i', 'k'), ('e', 'j', 'h'), ('e', 'k', 'i'), ('f', 'b', 'c'), ('f', 'c', 'b'),
    ('f', 'd', 'e'), ('f', 'e', 'd'), ('f', 'f', 'g'), ('f', 'g', 'f'), ('f', 'h', 'i'),
    ('f', 'i', 'h'), ('f', 'j', 'k'), ('f', 'k', 'j'), ('g', 'a', 'a'), ('g', 'b', 'b'),
    ('g', 'c', 'c'), ('g', 'd', 'd'), ('g', 'e', 'e'), ('g', 'f', 'f'), ('g', 'g', 'g'),
    ('g', 'h', 'h'), ('g', 'i', 'i'), ('g', 'j', 'j'), ('g', 'k', 'k'), ('h', 'd', 'k'),
    ('h', 'e', 'j'), ('h', 'f', 'i'), ('h', 'g', 'h'), ('h', 'h', 'g'), ('h', 'i', 'f'),
    ('h', 'j', 'e'), ('h', 'k', 'd'), ('i', 'd', 'j'), ('i', 'e', 'k'), ('i', 'f', 'h'),
    ('i', 'g', 'i'), ('i', 'h', 'f'), ('i', 'i', 'g'), ('i', 'j', 'd'), ('i', 'k', 'e'),
    ('j', 'd', 'i'), ('j', 'e', 'h'), ('j', 'f', 'k'), ('j', 'g', 'j'), ('j', 'h', 'e'),
    ('j', 'i', 'd'), ('j', 'j', 'g'), ('j', 'k', 'f'), ('k', 'd', 'h'), ('k', 'e', 'i'),
    ('k', 'f', 'j'), ('k', 'g', 'k'), ('k', 'h', 'd'), ('k', 'i', 'e'), ('k', 'j', 'f'),
    ('k', 'k', 'g')
]

# target hash (actual hash from `get_hash`)
target_hash = 4028159992  

# c++ hash function equivalent in Python
def custom_hash(value):
    hash_int = 5381
    for i in range(len(value)):
        hash_int = (((hash_int * 31) ^ (ord(value[i]) * 131)) + (i * 7)) & 0xFFFFFFFF
    return hash_int

# generate and check passwords
for v0, v2, v6 in filtered_combinations:
    for combo in product(allowed_chars, repeat=6):
        password = list(combo)
        password.insert(0, v0)  # placing v0 at position 0
        password.insert(2, v2)  # placing v2 at position 2
        password.insert(6, v6)  # placing v6 at position 6
        password_str = ''.join(password)
        
        # check if the password meets the criteria and matches the target hash
        if all(ch in allowed_chars and ch not in "/#1" for ch in password_str):
            if custom_hash(password_str) == target_hash:
                print("Password found:", password_str)
                break  # stopping once a match is found
