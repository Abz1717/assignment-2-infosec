import hashlib
import itertools
import math

alice_password = "5ef2c394d5b63e4175cd331c74c8453c3e36eb8f47f6d648397ff6c1314fd705"
root_password = "5e884898da28047151d0e56f8dc6292773603d0d6aabbdd62a11ef721d1542d8"

alice_password_sum = 338474
root_password_sum = 329013

def find_matching_string():
    # Character set to use for generating strings
    characters = 'abcdefghijklmnopqrstuvwxyz0123456789'
    check_alice, check_root = True, True
    # Set the maximum string length to consider
    string_length_max = 8
    i = 0
    for string_length in range(string_length_max):
        for combo in itertools.product(characters, repeat=string_length):
            if not check_root and not check_alice:
                return None
            i += 1
            if i%100000000 == 0: print(i)
            candidate = ''.join(combo)
            hash_hex = sha256_hash(candidate)
            if check_alice and get_checksum(hash_hex, "alice") == alice_password_sum:
                print("alice:", candidate, hash_hex)
                check_alice = False
            if check_root and get_checksum(hash_hex, "root") == root_password_sum:
                print("root:", candidate, hash_hex)
                check_root = False
                  # Return the matching string and its hash

    return None, None  # No match found

def sha256_hash(s):
    """Returns the SHA-256 hash of a string in hexadecimal format."""
    return hashlib.sha256(s.encode()).hexdigest()

def get_checksum(password, username):
    """
    Computes a checksum by concatenating the password and username,
    and applying a mathematical operation on overlapping triplets of characters.

    Args:
    - password (str): The password string.
    - username (str): The username string.

    Returns:
    - int: The computed checksum.
    """
    cat = password + username
    sum_result = 0

    for i in range(len(cat) - 2):
        # Convert characters to their ASCII integer values
        a = ord(cat[i])
        b = ord(cat[i + 1])
        c = ord(cat[i + 2])
        
        # Perform a floating-point multiply-add operation
        sum_result += (a * b) + c

    return sum_result

if __name__ == "__main__":
    find_matching_string()