# Ciphers Program🔒

This C++ program provides encryption and decryption using two popular cipher techniques: Caesar Cipher and Vigenère Cipher. It also includes functionality for automated decryption of Caesar Cipher using a dictionary-based approach to find potential valid plaintext.

### Features

- Caesar Cipher Encryption: Rotate each letter in a text by a specified number of positions.
- Caesar Cipher Decryption: Attempt to decrypt a Caesar Cipher by testing all possible rotations and comparing against a dictionary.
- Vigenère Cipher Encryption: Encrypt text using a keyword to apply a sequence of Caesar shifts.
- Dictionary Check: The program uses a dictionary file to validate words for automatic Caesar Cipher decryption.

### Input Format

- For Caesar Cipher, provide the text and the number of rotations.
- For Vigenère Cipher, provide the text and a keyword for encryption.
- For Decryption, the program will attempt to decrypt Caesar Cipher text by testing all 26 shifts and comparing words against the dictionary.

