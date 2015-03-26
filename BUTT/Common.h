#ifndef COMMON_H
#define COMMON_H

#include <set>
#include <cstdint>
#include <vector>
#include <string>
#include <sstream>

#define NUCL_BIT 2

#define NUCL_A 0
#define NUCL_C 1
#define NUCL_G 2
#define NUCL_U 3
#define NUCL_T 3

/**
 * Each oligo is encoded as a k-mer (2 bits) by encoding two bits per nucletoide:
 *
 * a = A = 00
 * c = C = 01
 * g = G = 10
 * u = U = 11
 * t = T = 11
 *
 * E.g. UCCUACGG = 0110100100101111 = 26927
 * Using uint32_t, this definition of k-mer therefore allows for k up to 16.
 */
typedef uint32_t KMer;

/**
 * @brief An ordered set of k-mers.
 */
typedef std::set<KMer> KMerSet;


/**
 * @brief Splits a string using delimiters
 * @param s the string
 * @param delim the delimiter
 * @param elems the vector to put results in
 * @return the vector elems
 */
static std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

/**
 * @brief Splits a string using delimiters
 * @param s the string
 * @param delim the delimiter
 * @return a vector of split string elements
 */
static std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

template<typename T>
std::ostream & operator<<(std::ostream & os, std::vector<T> vec)
{
    os<<"{ ";
    std::copy(vec.begin(), vec.end(), std::ostream_iterator<T>(os, " "));
    os<<"}";
    return os;
}

template<typename T, typename R>
std::ostream & operator<<(std::ostream & os, std::pair<T,R> pair)
{
    os<<"("<<pair.first<<","<<pair.second<<")";
    return os;
}

#endif // COMMON_H
