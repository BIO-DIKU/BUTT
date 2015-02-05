#ifndef COMMON_H
#define COMMON_H

#include <set>
#include <cstdint>

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

#endif // COMMON_H
