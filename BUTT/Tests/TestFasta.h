#ifndef TESTFASTA_H
#define TESTFASTA_H

#include <string>

class TestFasta
{
public:
    TestFasta(const std::string &fast_test_directory);

    bool runTests();

private:
    std::string fastaDirectory;

    /**
     * Test that well-formed entries are correctly read and that eof follows
     * Input:
     * >1 K#Bacteria;P#Proteobacteria
     * ATCGU atcgu
     * >1 K#Bacteria;P#Proteobacteria
     * atcgu
     * Expects:
     *   ("1 K#Bacteria;P#Proteobacteria", "ATCGU atcgu"),
     *   ("1 K#Bacteria;P#Proteobacteria", "atcgu")
     */
    bool test1();

    /**
     * Tests that newlines are stripped and whitespaces preserved in sequences.
     * Input:
     *
     *
     * >1
     *
     * at cg
     *
     *
     * ATCG
     *
     * >2
     * atcg
     *
     *
     *
     * Expected:
     *   ("1", "at cgATCG"),
     *   ("2", "atcg")
     */
    bool test2();

    /**
     * Tests that ">" doesnt lead to error when used within entry header or sequence
     * Input:
     * >1>2
     * AT>CG
     * Expected:
     *   ("1>2", "AT>CG")
     */
    bool test3();

    /**
     * Tests that empty header throws exception
     * Input
     * >
     * atcg
     * @brief test4
     * Expected: Exception
     */
    bool test4();

    /**
     * Tests that empty sequence followed by linebreak throws exception
     * Input
     * >1
     *
     * Expected: Exception
     */
    bool test5();

    /**
     * Tests that missing header throws exception
     * Input:
     * atcg
     * Expected: Exception
     */
    bool test6();

    /**
     * Tests that empty sequence followed by new header throws exception
     * >1
     * >2
     * atcg
     * Expected: Exception
     */
    bool test7();

    /**
     * Tests that empty file leads to empty set of entries
     * Input:
     * Expected:
     *   {}
     */
    bool test8();

    /**
     * Tests that truncated header followed by eof throws exception
     * Input:
     * >1
     * Expected: Exception
     */
    bool test9();
};

#endif // TESTFASTA_H
