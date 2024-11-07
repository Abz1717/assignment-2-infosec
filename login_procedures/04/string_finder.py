import hashlib
import itertools

def sha256_hash(s):
    """Returns the SHA-256 hash of a string in hexadecimal format."""
    return hashlib.sha256(s.encode()).hexdigest()

def find_matching_string1(target_prefix):
    """Attempts to find a string whose SHA-256 hash starts with the target_prefix."""
    # Character set to use for generating strings
    characters = 'abcdefghijklmnopqrstuvwxyz0123456789'

    # Set the maximum string length to consider
    string_length = 8
    i = 0
    for combo in itertools.product(characters, repeat=string_length):
        i += 1
        if i%100000000 == 0: print(i)
        candidate = ''.join(combo)
        hash_hex = sha256_hash(candidate)
        if hash_hex.startswith(target_prefix):
            return candidate, hash_hex  # Return the matching string and its hash

    return None, None  # No match found

def main1():
    target_hash = '5e884898'  # Example of a target prefix for the hash
    matching_string, matching_hash = find_matching_string1(target_hash)

    if matching_string:
        print(f"Matching string found: '{matching_string}' with hash: {matching_hash}")
    else:
        print("No matching string found.")

if __name__ == "__main__":
    main1()