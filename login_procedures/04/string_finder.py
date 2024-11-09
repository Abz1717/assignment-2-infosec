import hashlib
import itertools

def sha256_hash(s):
    return hashlib.sha256(s.encode()).hexdigest()

def find_matching_string1(target_prefix):
    characters = 'abcdefghijklmnopqrstuvwxyz0123456789'

    string_length = 8
    i = 0
    for combo in itertools.product(characters, repeat=string_length):
        i += 1
        if i%100000000 == 0: print(i)
        candidate = ''.join(combo)
        hash_hex = sha256_hash(candidate)
        if hash_hex.startswith(target_prefix):
            return candidate, hash_hex

    return None, None

def main():
    target_hash = '5e884898'
    matching_string, matching_hash = find_matching_string1(target_hash)
    if matching_string:
        print(f"Matching string found: '{matching_string}' with hash: {matching_hash}")
    else:
        print("No matching string found.")

if __name__ == "__main__":
    main()