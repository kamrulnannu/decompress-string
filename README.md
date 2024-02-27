This project is about decompress a compressed string.
Input is a compressed string of the format number[string] and the decompressed output

form should be the string written number times.

The input: 3[abc]4[ab]c  Would be output as abcabcabcababababc

One repetition can occur inside another. For example, 2[3[a]b] decompresses into aaabaaab

 Two solutions are provided:
 
    (a) Recursive approach
    
    (b) Iterative approach with stack<std::any>
    

Compile: g++ -std=c++17 decompress_string.cpp -o decompress

Some test results:

Please enter a valid Compresssed string: 3[abc]
DeCompressed String: abcabcabc
DeCompressed String v1: abcabcabc
Please enter a valid Compresssed string: abc2[xy]
DeCompressed String: abcxyxy
DeCompressed String v1: abcxyxy
Please enter a valid Compresssed string: 2[a3[xy]b]
DeCompressed String: axyxyxybaxyxyxyb
DeCompressed String v1: axyxyxybaxyxyxyb
Please enter a valid Compresssed string: 2[a3[xy]]b
DeCompressed String: axyxyxyaxyxyxyb
DeCompressed String v1: axyxyxyaxyxyxyb
Please enter a valid Compresssed string: T2[pq2[xy]]U
DeCompressed String: TpqxyxypqxyxyU
DeCompressed String v1: TpqxyxypqxyxyU
Please enter a valid Compresssed string: 3[abc]4[de]f
DeCompressed String: abcabcabcdedededef
DeCompressed String v1: abcabcabcdedededef
Please enter a valid Compresssed string: 2[3[a]b]
DeCompressed String: aaabaaab
DeCompressed String v1: aaabaaab
Please enter a valid Compresssed string: 2[ab2[xy]c]d
DeCompressed String: abxyxycabxyxycd
DeCompressed String v1: abxyxycabxyxycd
