#ifndef FASTA_H
#define FASTA_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

/**
 * @brief A sequence entry container.
 */
struct FastaEntry{
    /** Header info contained between '>' character and end-of-line */
    std::string header;
    /** Sequence info is all printable characters between two header-lines or a header-line and eof. */
    std::string sequence;
};

/**
 * @brief Exception thrown by Fasta class
 */
class FastaException: public std::exception {
public:
    FastaException(std::string &msg): exceptionMsg(msg){}
    FastaException(const FastaException &e): exceptionMsg(e.exceptionMsg){}
    const std::string exceptionMsg;
};

/**
 * @brief Class for parsing fasta-files
 */
class Fasta
{
public:
    /** @brief Set up a fasta-file for reading from the specified file */
    Fasta(const std::string &filePath);

    /**
     * @brief Read the next entry from the fasta-file.
     * If the file contains no more entries this method will return NULL.
     * Blank lines are ignored.
     */
    FastaEntry nextEntry();

    bool hasNextEntry();

private:
    std::ifstream inputStream;
    std::string nextHeader;
};

#endif // FASTA_H
