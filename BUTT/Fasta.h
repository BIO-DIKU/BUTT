#ifndef FASTA_H
#define FASTA_H

#include <string>
#include <vector>
#include <iostream>

/**
 * @brief A sequence entry container.
 */
struct {
    /** Header info contained between '>' character and end-of-line */
    std::string header;
    /** Sequence info is all printable characters between two header-lines or a header-line and eof. */
    std::string sequence;
} FastaEntry;

/**
 * @brief Exception thrown by Fasta class
 */
class FastaException: public std::exception {
public:
    FastaException(std::string &msg): exceptionMst(msg){}
    const std::string exceptionMsg;
};

/**
 * @brief Class for parsing fasta-files
 */
class Fasta
{
public:
    /** @brief Set up a fasta-file for reading from the specified file */
    Fasta(std::string filePath);

    /**
     * @brief Read the next entry from the fasta-file.
     * If the file contains no more entries this method will throw a FastaIOException
     */
    FastaEntry nextEntry();

    /**
     * @brief Indicates if the file contains any more entries.
     * This is the recommended way of detecting for eof.
     */
    bool hasNextEntry();

private:
    std::istream inputStream;
};

#endif // FASTA_H
