# SubstitutionCipher
Takes a partially-completed cipher key and a known keyword to decipher code

PROJECT DESCRIPTION

Suppose that we are trying to crack a substitution cipher and that we have some partial information that should help us be able to decode the encoded text. Write a C++ program that operates as described below.

Program should accept three command line arguments. Argument 1 and 2 are filenames and argument 3 is a string containing a word.

The first file will contain exactly two lines that represent a way to encode text. The first line will be a subset of the letters A-Z, and the corresponding characters on the second line will represent the encoding. For example, in the file shown below, the code letter for an A would be a P and the code for an E would be an X. This means that in an encoded piece of text, the letter X would represent an E in the original text. Note that because we only have partial information not all of the letters A…Z will necessarily appear on the first line.

ABCDEF…
PLMAXY…

The second file will be an encoded text. Only the letters A…Z will be encoded. All other whitespace or punctuation will be unchanged.

Since not all of the letters appear in file1, there may be a letter in the encoded text that you do not know how to decode. This is where the third argument is used. The third argument will be a word that is known to appear in the source text.

Your job is to try assigning corresponding letters to the parts of the cipher that are unknown until the word in the third argument appears in the decoded text.

Sample input:

file1:
ABCFGHIJKLMNPQRSTUVWXYZ
PDFZATMEBYOCSWINVXLJRUQ
(empty line)

file2:
VTK GHA EXOSKG HLKI VTK ZKCFK
(empty line)

./p1 file1 file2 DOG
THE DOG JUMPED OVER THE FENCE
You must do your own work; you must not share any code with any other person. If you violate this rule, you may receive an invitation to the dean’s office to discuss the penalties for academic misconduct.

Notes:

The word given in the third argument must appear standalone. If the third argument word appears inside another word but does not appear standalone, then the mapping is incorrect. For example, if the word is HAT, and if a mapping makes the word WHAT appear but HAT does not appear as a standalone word as well, then the mapping is incorrect.
Anything that is not A-Z counts as punctuation and should separate words.
HOW+ARE should be viewed as the words HOW and ARE.
HELLO, HOW should be viewed as the words HELLO and HOW.

All spaces, newlines, and characters must be present in the decrypted text. For example, if the text was

VTK GHA EXOSKG, HLKI+VTK
ZKCFK.!12@ TK

then the decrypted text should be

THE DOG JUMPED, OVER+THE
FENCE.!12@ HE

After the word is found in the text, only 0 or 1 characters may still need mapping. An additional mapping must be assigned and decrypted.
There will be only 1 valid solution. Your program will not be tested against any input that can create multiple correct answers.
The alphabet in file1 does not have to be in order from A-Z
Additional example:

file1:
EFGHIJLMNOPQRSTUWXYZD
UMNQOVHSZKECLYRXTBJPW
file2:
QUHHK, RKS NKR I YSIHH EOUDU KM EOU. YQU IWAOYUW QOS RK DKSU GIDF IR KZDU.
./a.out file1 file2 BACK
HELLO, TOM GOT A SMALL PIECE OF PIE. SHE ADVISED HIM TO COME BACK AT ONCE.
