# CS300 OpenSSL Hash Wrapper
This repository includes a wrapper around OpenSSL's hash functions (which typically have a very complex API and less-than-extensive documentation). 

We provide the following function: 
```c++
std::string hash_str(std::string input, int input_len)
```

This function consumes an `std::string` as well as its length and returns an `std::string` that is the hash of the string given. Hash functions have the property that hashing the same string twice will give you the same hash, but it's very difficult to go from the hash back to the original string. This is what makes them so secure!